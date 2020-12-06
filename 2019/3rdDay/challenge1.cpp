#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

std::vector<std::string> tokenise( std::string input )
{
    std::stringstream ssInput( input );
    std::vector<std::string> stream;

    std::string s;
	while( std::getline( ssInput, s, ',' ) ) {
		stream.push_back( s );
	}

    return stream;
}

struct vec2
{
    int x;
    int y;

    bool operator==(const vec2& v) const
    {
        return x == v.x && y == v.y;
    }
};

namespace std
{
    template <>
    struct hash<vec2>
    {
        size_t operator()( const vec2& v ) const
        {
            return v.x ^ v.y;
        }
    };
}

struct Wire
{
    vec2 Head = { 0, 0 };
    vec2 Origin = { 0, 0 };
    std::vector<vec2> Visited;
};

void step( std::vector<vec2>& path, vec2& pos, int steps, char dir )
{

    auto up     = []( vec2& p ) { p.y -= 1; };
	auto down   = []( vec2& p ) { p.y += 1; };
	auto left   = []( vec2& p ) { p.x -= 1; };
	auto right  = []( vec2& p ) { p.x += 1; };

    void (*stepSingle)(vec2&);

    switch ( dir )
    {
        case 'U': stepSingle = up; break;
        case 'D': stepSingle = down; break;
        case 'R': stepSingle = right; break;
        case 'L': stepSingle = left; break;
        default: break;
    }

	for( int i = 0; i < steps; i++ )
	{
		stepSingle( pos );
		path.push_back( pos );
	}

}

int main(int argc, char** argv)
{

    std::ifstream infile( argv[1] );

    std::string input;

    std::getline( infile, input );
    std::vector<std::string> wireS1 = tokenise( input );

    std::getline( infile, input );
    std::vector<std::string> wireS2 = tokenise( input );

    // Construct map of nodes
    // for each point a wire
    // lays on, one is added
    // to the node

    // Wires are assumed to start at 0,0

    Wire wire1;
    for ( auto& element : wireS1 )
    {

        // Seperate the direction from the displacement

        char direction = element[0];
        int displacement = std::stoi( element.substr( 1, element.size() ) );

        step(wire1.Visited, wire1.Head, displacement, direction);

        std::cout << "Wire 1 " << element << std::endl;

    }

    Wire wire2;
    for ( auto& element : wireS2 )
    {

        // Seperate the direction from the displacement

        char direction = element[0];
        int displacement = std::stoi( element.substr( 1, element.size() ) );

        step(wire2.Visited, wire2.Head, displacement, direction);

        std::cout << "Wire 2 " << element << std::endl;

    }

    auto find = []( std::vector<vec2> arr, vec2 el ) {
        for ( int i = 0; i < arr.size(); i++ )
            if ( arr[i] == el ) return i;
        return -1;
    };

    std::vector<int> intersectDistances;

    // This takes a good few seconds
	for ( int i = 0; i < wire1.Visited.size(); i++ )
    {

        vec2 v = wire1.Visited[i];
        if ( find( wire2.Visited, v ) != -1 )
        {
            std::cout << "Found : " << v.x << " " << v.y << std::endl;
            intersectDistances.push_back( std::abs( v.x ) + std::abs( v.y ) );
        }

    }

    int minDistance = *std::min_element( intersectDistances.cbegin(), intersectDistances.cend() );

    std::cout << "Minimum Distance to Intersect : " << minDistance << std::endl;

}
