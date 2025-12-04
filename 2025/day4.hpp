#pragma once
#include "aoc.hpp"

class Day04 : public AOCDay
{
public:
    Day04() {}
    ~Day04() {}
    int Day() override { return 4; }

    uint64_t PartOne(File& f) override
    {
        const auto grid = f.AsGrid<char>();

        int res = 0;

        for (int i = 0; i < grid.Width(); i++)
        {
            for (int j = 0; j < grid.Width(); j++)
            {
                if (grid.At(i, j) != '@') continue;
                auto neighbors = grid.Neighbours8(i, j);

                int rollsOfPaper = 0;
                for (auto* n : neighbors)
                {
                    if (*n == '@')
                    {
                        rollsOfPaper++;
                        if (rollsOfPaper > 4)
                        {
                            break;
                        }
                    }
                }

                if (rollsOfPaper < 4)
                {
                    res++;
                }
            }
        }

        return res;
    }

    int MovePossibleRolls(Grid<char>* grid)
    {
        int removed = 0;
        for (int i = 0; i < grid->Width(); i++)
        {
            for (int j = 0; j < grid->Width(); j++)
            {
                if (grid->At(i, j) != '@') continue;
                auto neighbors = grid->Neighbours8(i, j);

                int rollsOfPaper = 0;
                for (auto* n : neighbors)
                {
                    if (*n == '@')
                    {
                        rollsOfPaper++;
                        if (rollsOfPaper > 4)
                        {
                            break;
                        }
                    }
                }

                if (rollsOfPaper < 4)
                {
                    grid->ReplaceAt(i, j, '.');
                    removed++;
                }
            }
        }
        return removed;
    }

    uint64_t PartTwo(File& f) override
    {
        auto grid = f.AsGrid<char>();

        int removedRolls = 0;

        int removedLastTime = 0;
        do
        {
            removedLastTime = MovePossibleRolls(&grid);
            removedRolls += removedLastTime;
        } while (removedLastTime != 0);

        return removedRolls;
    }
};

ADD_AOC_DAY(Day04);
