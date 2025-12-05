#pragma once
#include "aoc.hpp"

#include <set>

class Day05 : public AOCDay
{
public:
    Day05() {}
    ~Day05() {}
    int Day() override { return 5; }

    std::vector<std::pair<uint64_t, uint64_t>> freshIDs;

    uint64_t PartOne(File& f) override
    {
        bool ranges = true;
        int ret = 0;
        for (auto line : f.Lines())
        {
            if (line == "")
            {
                ranges = false;
                continue;
            }

            if (ranges)
            {
                int dash = line.find('-', 0);
                uint64_t a = std::stoll(line.substr(0, dash));
                uint64_t b = std::stoll(line.substr(dash + 1));

                freshIDs.push_back({a, b});
            }
            else
            {
                uint64_t foodStuff = std::stoll(line);
                for (auto range : freshIDs)
                {
                    if (foodStuff >= range.first && foodStuff <= range.second)
                    {
                        ret++;
                        break;
                    }
                }
            }
        }
        return ret;
    }

    uint64_t PartTwo(File& f) override
    {
        // sort by first ID
        std::sort(freshIDs.begin(), freshIDs.end());

        uint64_t total = 0;
        uint64_t curL = freshIDs[0].first;
        uint64_t curR = freshIDs[0].second;

        for (size_t i = 1; i < freshIDs.size(); i++)
        {
            auto [L, R] = freshIDs[i];

            if (L > curR + 1)
            {
                total += (curR - curL + 1);
                curL = L;
                curR = R;
            }
            else
            {
                curR = std::max(curR, R);
            }
        }

        total += (curR - curL + 1);

        return total;
    }
};

ADD_AOC_DAY(Day05);
