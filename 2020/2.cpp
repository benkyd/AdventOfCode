#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

std::vector<std::string> readFile(std::string path)
{
    std::ifstream file(path);
    std::vector<std::string> input;
    std::string line;
    
    while(std::getline(file, line))
    {
        input.push_back(line);
    }
    return input;
}


int main()
{
    std::vector<std::string> input = readFile("./2.txt");

    int total = 0;
    for (auto& line : input)
    {
        std::vector<std::string> parts = split(line, " ");

        int lower, upper;
        std::vector<std::string> bounds = split(parts[0], "-");
        lower = std::stoi(bounds[0]);
        upper = std::stoi(bounds[1]);

        char searchterm = parts[1][0];

        int count = 0;
        for (int i = 0; i < parts[2].length(); i++)
            if (parts[2][i] == searchterm) count++;

        if (count >= lower && count <= upper) total++;
    }

    std::cout << "Part 1, valid passwords: " << total << std::endl;

    total = 0;
    for (auto& line : input)
    {
        std::vector<std::string> parts = split(line, " ");

        int first, second;
        std::vector<std::string> bounds = split(parts[0], "-");
        first = std::stoi(bounds[0]) - 1;
        second = std::stoi(bounds[1]) - 1;

        char searchterm = parts[1][0];

        // A terrible logical XOR
        if (!(parts[2][first] == searchterm) != !(parts[2][second] == searchterm)) total++;
    }

    std::cout << "Part 2, valid passwords: " << total << std::endl;

}
