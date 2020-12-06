#include <algorithm>
#include <iostream>
#include <string>

bool checkPassword( std::string pass )
{

    // Is less than 6
    if ( pass.length() > 6 || pass.length() < 6 ) return false;

    // Digets never decrease
    bool decreases = true;
    for ( int i = 1; i < pass.length(); i++ )
        if ( pass[i - 1] > pass[i] ) decreases = false;

    if ( !decreases ) return false;

    // No repeats ( conform w part 2 rule )
    if ( std::any_of( pass.begin(), pass.end(), 
    [&]( auto d ) {
        return std::count( pass.begin(), pass.end(), d ) == 2; 
    } ) )
    {
        return true;
    }

    return false;

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
