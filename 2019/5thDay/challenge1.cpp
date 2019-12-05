#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> tokenise( std::string input )
{
    std::stringstream ssInput( input );
    std::vector<int> stream;

    std::string s;
	while( std::getline( ssInput, s, ',' ) ) {
		stream.push_back( std::stoi( s ) );
	}

    return stream;
}

class IntCodeCPU
{
public:

    IntCodeCPU();

    std::vector<int> Program;
    int ProgramCounter;

    void SetProgram( std::vector<int> program )
    {
        Program = program;
    }

    void RegisterOpcode( int opcode )
    {

    }



};

int main(int argc, char** argv)
{

    std::ifstream infile( argv[1] );

    std::string input;
    std::getline( infile, input );

    std::vector<int> program = tokenise( input );

}
