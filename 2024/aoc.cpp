#include <iostream>

#include "aoc.hpp"
#include "day1.hpp"


int main(int argc, char** argv)
{
    std::cout << "Advent of Code 2024 runner" << std::endl;
    std::cout << "©Ben Kyd 2025, All Rights Reserved" << std::endl;

    // Very shit command-line parsing :tm:
    int run_day = 0;
    std::filesystem::path base = "./";

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        // Day flag
        if (arg == "-d")
        {
            if (i + 1 >= argc)
            {
                std::cerr << "Error: -d requires a day number\n";
                return 1;
            }
            ++i;
            run_day = std::atoi(argv[i]);
            std::cout << "Selected day to run: " << run_day << "\n";
        }

        // Path flag
        if (arg == "-p" || arg == "--path")
        {
            if (i + 1 >= argc)
            {
                std::cerr << "Error: " << arg << " requires a path\n";
                return 1;
            }
            ++i;
            base /= argv[i];
            std::cout << "Selected base path: " << base.string() << "\n";
        }

        // Help flag
        if (arg == "help" || arg == "--help" || arg == "-h")
        {
            std::cout << "\nUsage:\n"
                      << "  -d [day]    Run a specific day\n"
                      << "  -p [path]   Set a base path for input\n"
                      << "  help        Show this help message\n"
                      << "  (no args)   Run all days\n";
            return 0;
        }

        // Unknown argument
        if (arg != "-d" && arg != "-p" && arg != "--path" &&
            arg != "help" && arg != "--help" && arg != "-h")
        {
            std::cerr << "Unknown argument: " << arg << "\n"
                      << "Use 'help' for usage information.\n";
            return 1;
        }
    }
    //
    // Run days
    if (run_day == 0)
    {
        for (auto& [num, day] : GetRegisteredDays())
        {
            std::cout << "Running Day " << num << ":\n";

            std::string filename = std::to_string(num) + ".txt";
            std::filesystem::path path = base / filename;

            std::cout << "Reading " << path << "..." << std::endl;
            File file{path};

            int partOne = day->PartOne(file);
            int partTwo = day->PartTwo(file);

            std::cout << "Part 1: " << partOne << "\n";
            std::cout << "Part 2: " << partTwo << "\n";
        }
    } else
    {
        for (auto& [num, day] : GetRegisteredDays(run_day))
        {
            std::cout << "Running only Day " << num << ":\n";

            std::string filename = std::to_string(num) + ".txt";
            std::filesystem::path path = base / filename;

            std::cout << "Reading " << path << "..." << std::endl;
            File file{path};

            int partOne = day->PartOne(file);
            int partTwo = day->PartTwo(file);

            std::cout << "Part 1: " << partOne << "\n";
            std::cout << "Part 2: " << partTwo << "\n";
        }
    }

}

