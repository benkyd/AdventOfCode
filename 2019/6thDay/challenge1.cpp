#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

std::unordered_map<std::string, std::string> mapise( std::vector<std::string> input )
{

    std::unordered_map<std::string, std::string> ret;

    for ( auto& str : input )
    {
        std::string first = str.substr(0, 3);
        std::string second = str.substr(4, str.size());

        ret[first] = second;
        std::cout << first << " " << second << std::endl;
    }

    return ret;

}

int main(int argc, char** argv)
{
    std::ifstream infile( argv[1] );

    std::vector<std::string> lines;

    std::string line;
    while (!infile.eof()) 
    {

        std::getline(infile, line);
        if ( line.length() == 0 ) continue;
        lines.push_back(line);

    }

    int accumilator = 0;

    auto map = mapise( lines );

    std::unordered_map<std::string, std::string>::iterator it;
    for (it = map.begin(); it != map.end(); it++)
    {

        

    }

    std::cout << "Sum of direct and indirect orbits : " << accumilator << std::endl;

}
