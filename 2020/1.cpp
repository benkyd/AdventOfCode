#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main()
{
    std::ifstream file ("./1i.txt");
    std::vector<int> input;
    std::string line;
    
    while(std::getline(file, line))
    {
        input.push_back(std::stoi(line));
    }

    int found = 0;

    for (auto& i : input)
    {
        for (auto j : input)
        {
            if (i + j == 2020)
            {
                found = i * j;
                break;
            }
        }
        if (found != 0)
            break;
    }

    std::cout << "Part 1, 2 entries that sum to 2020: " << found << std::endl;
    found = 0;

    for (auto& i : input)
    {
        for (auto j : input)
        {
            for (auto k : input)
            {
                if (i + j + k == 2020)
                {
                    found = i * j * k;
                    break;
                }
            }
            if (found != 0)
                break;
        }
        if (found != 0)
            break;
    }
    
    std::cout << "Part 2, 3 entries that sum to 2020: " << found << std::endl;

}
