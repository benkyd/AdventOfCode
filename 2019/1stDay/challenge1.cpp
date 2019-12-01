#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

int main(int argc, char** argv)
{
    std::ifstream infile( argv[1] );

    int accumilator = 0;

    // for ( std::string line; !infile.eof(); std::getline( infile, line ) )
    // {

    //     if ( line.length() == 0 ) continue;
    //     accumilator += (std::stoi( line ) / 3) - 2;

    // }

    std::string line;
    while (!infile.eof()) 
    {

        std::getline(infile, line);
        if ( line.length() == 0 ) continue;
        accumilator += (std::stoi( line ) / 3) - 2;

    }

    std::cout << "Sum of the fuel requrements : " << accumilator << std::endl;

}
