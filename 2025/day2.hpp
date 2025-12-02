#include "aoc.hpp"

#include <algorithm>
#include <unordered_map>

class Day02 : public AOCDay
{
public:
    Day02() {}
    ~Day02() {}
    int Day() override {return 2;}

    uint64_t PartOne(File& f) override
    {
        f.SplitBy(",");

        uint64_t res = 0;

        // Range of ID's (11-22)
        for (auto range : f.TokensForLine(0))
        {
            int dash = range.Data.find('-', 0);

            uint64_t a = std::stoll(range.Data.substr(0, dash));
            uint64_t b = std::stoll(range.Data.substr(dash + 1));

            for (uint64_t i = a; i <= b; i++)
            {
                // Convert number back into string
                std::string current = std::to_string(i);
                // import 'is-odd' lol
                if (current.length() & 1) continue;

                int mid = current.length() / 2;

                uint64_t l = std::stoll(current.substr(0, mid));
                uint64_t r = std::stoll(current.substr(mid));

                if (l == r)
                {
                    res += i;
                }
            }
        }

        return res;
    }

    uint64_t PartTwo(File& f) override
    {
        f.SplitBy(",");

        uint64_t res = 0;

        // For every range like "11-22" in line 0
        for (auto range : f.TokensForLine(0))
        {
            int dash = range.Data.find('-', 0);

            uint64_t a = std::stoll(range.Data.substr(0, dash));
            uint64_t b = std::stoll(range.Data.substr(dash + 1));

            // Loop every ID in the range
            for (uint64_t id = a; id <= b; ++id)
            {
                std::string s = std::to_string(id);
                int digits = s.length();

                bool invalid = false;

                for (int L = 1; L <= digits / 2 && !invalid; ++L)
                {
                    // MUST divide evenly, otherwise blocks won't align
                    if (digits % L != 0)
                        continue;

                    uint64_t base = 1;
                    for (int i = 0; i < L; i++)
                        base *= 10;  // base = 10^L

                    uint64_t block = id % base;
                    uint64_t tail = id;
                    int count = 0;

                    while (tail > 0)
                    {
                        if (tail % base != block)
                            break;

                        tail /= base;
                        count++;
                    }

                    if (tail == 0 && count >= 2)
                        invalid = true;
                }

                if (invalid)
                    res += id;
            }
        }

        return res;
    }

};

ADD_AOC_DAY(Day02);

