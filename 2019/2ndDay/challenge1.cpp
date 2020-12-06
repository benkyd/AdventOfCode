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

    std::vector<int> program = tokenise( input );

    program[1] = 12; 
    program[2] = 2; 

    for ( int i = 0; i < program.size(); i += 4 ) 
    {

        int opcode = program[i];

        std::cout << "Opcode : " << opcode << std::endl;

        int operandLocA = program[i + 1]; 
        int operandLocB = program[i + 2];

        std::cout << "Operand locations : " << operandLocA << ", " << operandLocB << std::endl;

        int operandA = program[operandLocA];
        int operandB = program[operandLocB];

        int resLoc = program[i + 3];
        
        std::cout << "Result location : " << resLoc << std::endl;

        if ( opcode == Add )
            program[resLoc] = operandA + operandB;
        else if ( opcode == Multiply )
            program[resLoc] = operandA * operandB;
        else if ( opcode == End )
        {
            std::cout << "Program end" << std::endl << std::endl;
            break;
        }

        std::cout << std::endl;

    }


    std::cout << "Program end state : ";
    for ( auto& i : program )
        std::cout << i << " ";
    std::cout << std::endl;

}
