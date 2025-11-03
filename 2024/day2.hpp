#include "aoc.hpp"

class Day02 : public AOCDay
{
public:
    Day02() {}
    ~Day02() {}
    int Day() override {return 2;}

    int PartOne(File& f) override
    {
        f.SplitBy(" ");

        int result_bad = 0;

        for (int i = 0; i < f.Lines().size(); i++)
        {
            bool lastDirection;
            bool first = true;
            for (const auto& tokenPair : f.ChunkView(i, 2, 1))
            {
                int token = std::atoi(tokenPair[0].Data.c_str());
                int nextToken = std::atoi(tokenPair[1].Data.c_str());

                int diff = token - nextToken;
                bool direction = diff > 0;

                if (first)
                {
                    lastDirection = direction;
                    first = false;
                }

                if (std::abs(diff) > 3
                 || token == nextToken
                 || direction != lastDirection)
                {
                    result_bad++;
                    break;
                }

                lastDirection = direction;
                first = false;
            }
        }

        int result = f.Lines().size() - result_bad;

        return result;
    }

    int PartTwo(File&) override
    {
    }
};

ADD_AOC_DAY(Day02);

