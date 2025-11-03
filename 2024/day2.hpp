#include "aoc.hpp"

class Day02 : public AOCDay
{
public:
    Day02() {}
    ~Day02() {}
    int Day() override {return 2;}

    bool isSafe(const std::vector<int>& levels)
    {
        if (levels.size() < 2)
            return true;

        int dir = (levels[1] - levels[0] > 0) ? 1 : -1;

        for (size_t i = 1; i < levels.size(); ++i)
        {
            int diff = levels[i] - levels[i - 1];

            if (diff == 0)
                return false;
            if (std::abs(diff) > 3)
                return false;
            if ((diff > 0 ? 1 : -1) != dir)
                return false;
        }

        return true;
    }

    bool isSafeWithDampener(const std::vector<int>& levels)
    {
        // Already safe
        if (isSafe(levels))
            return true;

        // BRUTE FORCE
        for (size_t i = 0; i < levels.size(); ++i)
        {
            std::vector<int> copy = levels;
            copy.erase(copy.begin() + i);
            if (isSafe(copy))
                return true;
        }

        return false;
    }

    int PartOne(File& f) override
    {
        f.SplitBy(" ");

        int safe = 0;

        for (int i = 0; i < f.Lines().size(); ++i)
        {
            std::vector<int> nums;
            for (auto& token : f.TokensForLine(i))
                nums.push_back(std::atoi(token.Data.c_str()));

            if (isSafe(nums))
                safe++;
        }

        return safe;
    }

    int PartTwo(File& f) override
    {
        int safe = 0;

        for (int i = 0; i < f.Lines().size(); ++i)
        {
            std::vector<int> nums;
            for (auto& token : f.TokensForLine(i))
                nums.push_back(std::atoi(token.Data.c_str()));

            if (isSafeWithDampener(nums))
                safe++;
        }

        return safe;
    }
};

ADD_AOC_DAY(Day02);

