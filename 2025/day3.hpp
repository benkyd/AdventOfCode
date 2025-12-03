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

    std::pair<int,int> FindNextBiggestNoOffset(std::string bank, int startOffset, int endOffset)
    {
        int biggest = 0, biggestIndex = 0;
        for (int i = startOffset; i < bank.length() - endOffset; i++)
        {
            if (bank[i] - '0' > biggest)
            {
                biggest = bank[i] - '0';
                biggestIndex = i + 1;
            }
        }

        return {biggest, biggestIndex};
    }

    uint64_t PartTwo(File& f) override
    {
        uint64_t totalJoltage = 0;

        for (auto bank : f.Lines())
        {
            uint64_t joltage = 0;
            int start = 0;

            for (int i = 0; i < 12; i++)
            {
                joltage *= 10;

                auto res = FindNextBiggestNoOffset(bank, start, 12 - i);

                start = res.second;
                joltage += res.first - '0';
            }

            std::cout << joltage << std::endl;

            totalJoltage += joltage;
        }

        return totalJoltage;
    }

};

ADD_AOC_DAY(Day03);

