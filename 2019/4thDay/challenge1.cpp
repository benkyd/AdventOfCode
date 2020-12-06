#include <iostream>
#include <string>

bool checkPassword( std::string pass )
{

    // Is less than 6
    if ( pass.length() > 6 || pass.length() < 6 ) return false;

    // Have any repeats
    bool repeats = false;
    char lastr = pass[0];
    for ( int i = 1; i < pass.length(); i++ )
    {
        if ( lastr == pass[i] ) repeats = true;
        lastr = pass[i];
    }

    if ( !repeats ) return false;

    // Digets never decrease
    bool decreases = true;
    for ( int i = 1; i < pass.length(); i++ )
        if ( pass[i - 1] > pass[i] ) decreases = false;

    if ( !decreases ) return false;

    return true;

}

int main(int argc, char** argv)
{
    
    int upper = 893698;
    int lower = 367479;

    int accumilator = 0;
    for ( int i = lower; i < upper; i++ )
        if ( checkPassword( std::to_string( i ) ) )
            accumilator++;

    std::cout << "There are : " << accumilator << " valid passwords" << std::endl;

}
