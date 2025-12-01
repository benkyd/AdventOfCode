#include "aoc.hpp"

#include <algorithm>
#include <unordered_map>

class Day01 : public AOCDay
{
public:
    Day01() {}
    ~Day01() {}
    int Day() override {return 1;}

    int dial = 50;
    void RotateDial(int diff)
    {
        dial = (dial + diff) % 100;
        if (dial < 0) dial += 100;
    }

    int PartOne(File& f) override
    {
        f.SplitByIndex(1);

        dial = 50;
        int res = 0;
        for (const auto& lineTokens : f)
        {
            char direction = (char)lineTokens[0].Data[0];
            int amount = std::stoi(lineTokens[1].Data);

            if (direction == 'L')
            {
                amount = -amount;
            }

            RotateDial(amount);

            if (dial == 0) res++;
        }

        return res;
    }

    int PartTwo(File& f) override
    {
        f.SplitByIndex(1);

        dial = 50;
        int res = 0;
        for (const auto& lineTokens : f)
        {
            char direction = (char)lineTokens[0].Data[0];
            int amount = std::stoi(lineTokens[1].Data);

            int dir = 1;
            if (direction == 'L')
            {
                dir = -1;
            }

            while (amount > 0)
            {
                RotateDial(dir);
                if (dial == 0) res++;
                amount--;
            }
        }

        return res;
    }
};

ADD_AOC_DAY(Day01);

