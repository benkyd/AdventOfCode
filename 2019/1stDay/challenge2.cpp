#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

int fuelForMass ( int mass, int accumilator = 0 ) 
{

    int res = (mass / 3) - 2;
    if ( res > 0 ) 
        return fuelForMass( res, accumilator + res );

    return res;

};

int main(int argc, char** argv)
{
    std::ifstream infile( argv[1] );

    int accumilator = 0;


    std::string line;
    while (!infile.eof()) 
    {

        std::getline(infile, line);
        if ( line.length() == 0 ) continue;
        accumilator += fuelForMass( std::stoi( line ) );
        
    }

    std::cout << "Sum of the fuel requrements : " << accumilator << std::endl;

}
