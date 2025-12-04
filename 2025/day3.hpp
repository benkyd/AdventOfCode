#include "aoc.hpp"

#include <algorithm>

class Day03 : public AOCDay
{
public:
    Day03() {}
    ~Day03() {}
    int Day() override {return 3;}

    uint64_t PartOne(File& f) override
    {
        uint64_t totalJoltage = 0;

        for (auto bank : f.Lines())
        {
            int joltage = 0;
            // find biggest (can't be last)
            int biggest = 0;
            int biggestIndex = 0;
            for (int i = 0; i < bank.length() - 1; i++)
            {
                if (bank[i] - '0' > biggest)
                {
                    biggest = bank[i] - '0';
                    biggestIndex = i + 1;
                }
            }

            joltage = biggest;
            joltage *= 10;

            biggest = 0;


            for (int i = biggestIndex; i < bank.length(); i++)
            {
                if (bank[i] - '0' > biggest)
                {
                    biggest = bank[i] - '0';
                }
            }

            joltage += biggest;

            totalJoltage += joltage;
        }

        return totalJoltage;
    }


    std::pair<int,int> FindNextBiggest(const std::string& s, int start, int k)
    {
        int remaining = 12 - k - 1;
        int lastAllowed = s.size() - remaining;   // inclusive upper bound

        int bestDigit = -1;
        int bestIndex = start;

        for (int i = start; i < lastAllowed; i++)
        {
            int d = s[i] - '0';
            if (d > bestDigit)
            {
                bestDigit = d;
                bestIndex = i;
            }
        }

        return { bestDigit, bestIndex + 1 };
    }

    uint64_t PartTwo(File& f) override
    {
        uint64_t totalJoltage = 0;

        for (auto bank : f.Lines())
        {
            uint64_t joltage = 0;
            int start = 0;

            for (int k = 0; k < 12; k++)
            {
                joltage *= 10;

                auto res = FindNextBiggest(bank, start, k);

                joltage += res.first;
                start = res.second;
            }

            totalJoltage += joltage;
        }

        return totalJoltage;
    }

};

ADD_AOC_DAY(Day03);

