
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
        const size_t height = grid.Height();
        const size_t width = grid.Width();
        const char* neighbours[8];

        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                if (grid.At(i, j) != '@') continue;

                size_t count = grid.Neighbours8(i, j, neighbours);

                // Unroll, unroll unroll
                int rollsOfPaper = 0;
                rollsOfPaper += (count > 0 && *neighbours[0] == '@');
                rollsOfPaper += (count > 1 && *neighbours[1] == '@');
                rollsOfPaper += (count > 2 && *neighbours[2] == '@');
                rollsOfPaper += (count > 3 && *neighbours[3] == '@');
                rollsOfPaper += (count > 4 && *neighbours[4] == '@');
                rollsOfPaper += (count > 5 && *neighbours[5] == '@');
                rollsOfPaper += (count > 6 && *neighbours[6] == '@');
                rollsOfPaper += (count > 7 && *neighbours[7] == '@');

                if (rollsOfPaper < 4) res++;
            }
        }

        return res;
    }

    uint64_t PartTwo(File& f) override
    {
        const auto input = f.AsGrid<char>();

        const size_t width = input.Width();
        const size_t height = input.Height();
        const char* neighbours[8];

        std::vector<uint8_t> counts(width * height);

        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                const size_t idx = i * width + j;

                if (input.At(i, j) == '.')
                {
                    counts[idx] = 255;
                    continue;
                }

                size_t count = input.Neighbours8(i, j, neighbours);

                uint8_t roll_count = 0;
                for (size_t k = 0; k < count; k++)
                {
                    roll_count += (*neighbours[k] != '.');
                }

                counts[idx] = roll_count;
            }
        }

        int64_t removed = 0;
        bool updated = true;

        Grid<uint8_t> grid(height, width);
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                grid.ReplaceAt(i, j, counts[i * width + j]);
            }
        }

        while (updated)
        {
            updated = false;

            for (size_t i = 0; i < height; i++)
            {
                for (size_t j = 0; j < width; j++)
                {
                    uint8_t val = grid.At(i, j);
                    if (val >= 4) continue;

                    updated = true;
                    grid.ReplaceAt(i, j, 255);
                    removed++;

                    size_t count = grid.Neighbours8(i, j, (const uint8_t**)neighbours);
                    for (size_t k = 0; k < count; k++)
                    {
                        size_t ni, nj;
                        // AAAAA
                        const uint8_t* base = &grid.At(0, 0);
                        size_t offset = (const uint8_t*)neighbours[k] - base;
                        ni = offset / width;
                        nj = offset % width;

                        uint8_t nval = grid.At(ni, nj);
                        if (nval < 255 && nval > 0)
                        {
                            grid.ReplaceAt(ni, nj, nval - 1);
                        }
                    }
                }
            }
        }

        return removed;
    }

};

ADD_AOC_DAY(Day04);

