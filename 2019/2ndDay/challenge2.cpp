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
    while( std::getline( ssInput, s, ',' ) )
    {
        stream.push_back( std::stoi( s ) );
    }

    return stream;
}

enum Opcodes
{
    Add = 1,
    Multiply = 2,
    End = 99
};

int main(int argc, char** argv)
{

    std::ifstream infile( argv[1] );

    std::string input;
    std::getline( infile, input );

    std::vector<int> program;

    for ( int noun = 0; noun < 100; noun++ )
    for ( int verb = 0; verb < 100; verb++ )
    {

        program = tokenise( input );

        // Noun
        program[1] = noun; 
        // Verb
        program[2] = verb;

        for ( int i = 0; i < program.size(); i += 4 ) 
        {

            int opcode = program[i];

            int operandA = program[program[i + 1]];
            int operandB = program[program[i + 2]];

            int resLoc = program[i + 3];

            if ( opcode == Add )
                program[resLoc] = operandA + operandB;
            else if ( opcode == Multiply )
                program[resLoc] = operandA * operandB;
            else if ( opcode == End )
                break;

        }

        if ( program[0] == 19690720 )
        {
            std::cout << "Solution found : " << noun << " " << verb << std::endl;
            std::cout << "Solution answer : " << 100 * noun + verb << std::endl;
        }

    }

    std::cout << std::endl << "Program end state : ";
    for ( auto& i : program )
        std::cout << i << " ";
    std::cout << std::endl;

}
