#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <math.h>

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

std::unordered_map<vec2, int> genPath( std::vector<std::string> wire )
{
    std::unordered_map<vec2, int> path;
    vec2 pos = { 0, 0 };
    path[pos] = 0;

    auto up     = []( vec2& p ) { p.y -= 1; };
	auto down   = []( vec2& p ) { p.y += 1; };
	auto left   = []( vec2& p ) { p.x -= 1; };
	auto right  = []( vec2& p ) { p.x += 1; };

    void (*stepSingle)(vec2&);

    int stepCounter = 0;

    for ( auto& element : wire )
    {
        char dir = element[0];
        int steps = std::stoi( element.substr( 1, element.size() ) );

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
            path[pos] = ++stepCounter;
        }
    }

    return path;
}

int main(int argc, char** argv)
{

    std::ifstream infile( argv[1] );

    std::string input;

    std::getline( infile, input );
    std::vector<std::string> wireS1 = tokenise( input );

    std::getline( infile, input );
    std::vector<std::string> wireS2 = tokenise( input );

    auto path1 = genPath(wireS1);
    auto path2 = genPath(wireS2);

    int res = INFINITY;

    for ( auto [pos, steps] : path2 )
    {
        // Intersect
        if ( path1.count( pos ) > 0 )
        {
            std::cout << pos.x << ":" << pos.y << " " << steps << std::endl;
            if ( steps == 0 ) continue;
            res = std::min( res, path1[pos] + path2[pos] );
        }
    }

    std::cout << "Shortest Distance to Complete : " << res << std::endl;

}
