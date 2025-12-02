#include "aoc.hpp"

#include <algorithm>
#include <unordered_map>

class Day02 : public AOCDay
{
public:
    Day02() {}
    ~Day02() {}
    int Day() override {return 2;}

    int PartOne(File& f) override
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

        std::cout << "The answer doesn't fit in int : "<< res << std::endl;
        return res;
    }

    int PartTwo(File& f) override
    {
        f.SplitBy(",");

        uint64_t res = 0;

        for (auto range : f.TokensForLine(0))
        {
            int dash = range.Data.find('-', 0);

            uint64_t a = std::stoll(range.Data.substr(0, dash));
            uint64_t b = std::stoll(range.Data.substr(dash + 1));

            for (uint64_t i = a; i <= b; i++)
            {
                std::string current = std::to_string(i);
                int n = current.length();

                bool invalid = false;

                // Try every possible substring start (i)
                for (int start = 0; start < n && !invalid; start++)
                {
                    std::string accum;

                    // Build accum char-by-char
                    for (int end = start; end < n && !invalid; end++)
                    {
                        accum.push_back(current[end]);

                        int len = accum.length();
                        int remaining = n - start;

                        // Now check if repeats match
                        bool matches = true;

                        for (int rep = 0; rep < remaining / len; rep++)
                        {
                            if (current.compare(start + rep * len, len, accum) != 0)
                            {
                                matches = false;
                                break;
                            }
                        }

                        // Must be at least two repeats
                        if (matches && remaining / len >= 2)
                        {
                            invalid = true;
                            break;
                        }
                    }
                }

            if (invalid)
                res += i;
        }
    }


        std::cout << "The answer doesn't fit in int : "<< res << std::endl;
        return res;
    }
};

ADD_AOC_DAY(Day02);

