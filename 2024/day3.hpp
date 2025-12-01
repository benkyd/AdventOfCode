#include "aoc.hpp"

#include <cctype>

class Day03 : public AOCDay
{
public:
    Day03() {}
    ~Day03() {}
    int Day() override {return 3;}

    int PartOne(File& f) override
    {
        int result = 0;
        for (std::string input : f.Lines())
        {
            // for each char
            bool searchingParams = false;
            bool firstComma = false;
            bool closeBrace = false;
            std::string leftS;
            int left = -1;
            std::string rightS;
            int right = -1;

            for (int i = 0; i < input.length(); i++)
            {
                if (closeBrace)
                {
                    std::cout << "mul(" << left << "," << right << ")=" << left*right << std::endl;
                    if (left != -1 && right != -1)
                    {
                        result += left * right;
                    } else
                    {
                        std::cout << "Failed to parse" << std::endl;
                    }
                    searchingParams = false;
                    firstComma = false;
                    closeBrace = false;
                    leftS = "";
                    left = 0;
                    rightS = "";
                    right = 0;
                    i -= 2;
                    continue;
                }

                if (searchingParams)
                {
                    if (!firstComma)
                    {
                        if (input[i] == ',')
                        {
                            left = std::atoi(leftS.c_str());
                            firstComma = true;
                            continue;
                        }
                        leftS += input[i];
                    }

                    if (!closeBrace && firstComma)
                    {
                        if (input[i] == ')')
                        {
                            right = std::atoi(rightS.c_str());
                            closeBrace = true;
                            continue;
                        }
                        rightS += input[i];
                    }
                    if (std::isdigit(input[i]) == 0)
                    {
                        searchingParams = false;
                        firstComma = false;
                        closeBrace = false;
                        leftS = "";
                        left = 0;
                        rightS = "";
                        right = 0;
                        std::cout << "found bad char : " << input[i] << " IsDigit? : " << std::isdigit(input[i]) << std::endl;
                        continue;
                    }
                }

                if (input[i] == 'm' && input[i + 1] == 'u' && input[i + 2] == 'l' && input[i + 3] == '(')
                {
                    i = i + 3;
                    continue;
                    searchingParams = true;
                }
            }
        }

        return result;
    }

    int PartTwo(File& f) override
    {
    }
};

ADD_AOC_DAY(Day03);

