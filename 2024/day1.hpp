#include "aoc.hpp"

#include <algorithm>
#include <unordered_map>

class Day01 : public AOCDay
{
public:
    Day01() {}
    ~Day01() {}
    int Day() override {return 1;}

    std::vector<int> col1;
    std::vector<int> col2;

    int PartOne(File& f) override
    {
        f.SplitBy("   ");

        for (const auto& lineTokens : f)
        {
            for (const auto& token : lineTokens)
            {
                if (token.Col == 0)
                    col1.push_back(std::atoi(token.Data.c_str()));

                if (token.Col == 1)
                    col2.push_back(std::atoi(token.Data.c_str()));
            }
        }

        std::sort(col1.begin(), col1.end());
        std::sort(col2.begin(), col2.end());

        int res = 0;
        for (int i = 0; i < col1.size(); i++)
        {
            res += std::abs(col1[i] - col2[i]);
        }

        return res;
    }

    int PartTwo(File&) override
    {
        // Num of times each number appears in col2
        std::unordered_map<int, int> hits;

        for (int i = 0; i < col2.size(); i++)
        {
            hits[col2[i]] += 1;
        }

        int res = 0;
        for (int i = 0; i < col1.size(); i++)
        {
            res += (col1[i] * hits[col1[i]]);
        }

        return res;
    }
};

ADD_AOC_DAY(Day01);

