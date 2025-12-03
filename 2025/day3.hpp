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

            std::cout << biggest;
            biggest = 0;


            for (int i = biggestIndex; i < bank.length(); i++)
            {
                if (bank[i] - '0' > biggest)
                {
                    biggest = bank[i] - '0';
                }
            }
            std::cout << biggest << std::endl;

            joltage += biggest;

            totalJoltage += joltage;
        }

        return totalJoltage;
    }

    uint64_t PartTwo(File& f) override
    {
    }

};

ADD_AOC_DAY(Day03);

