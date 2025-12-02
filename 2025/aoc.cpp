#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "aoc.hpp"
#include "day1.hpp"
#include "day2.hpp"
#include "day3.hpp"

void GenerateDay(int day, std::filesystem::path base)
{
    std::cout << "Ganerating template for day " << day << std::endl;
    std::ostringstream className;
    className << "Day" << std::setw(2) << std::setfill('0') << day; // Day01
    std::string classStr = className.str();

    std::string headerName = "day" + std::to_string(day) + ".hpp";  // day1.hpp
    std::string inputName  = std::to_string(day) + ".txt";          // 1.txt

    std::filesystem::path headerPath = base / headerName;
    std::filesystem::path inputPath  = base / inputName;

    if (std::filesystem::exists(headerPath)) {
        std::cerr << headerName << " already exists. Aborting." << std::endl;
        return;
    }

    std::ofstream out(headerPath);
    if (!out) {
        std::cerr << "Failed to write " << headerName << std::endl;
        return;
    }

    out << "#pragma once\n";
    out << "#include \"aoc.hpp\"\n\n";
    out << "class " << classStr << " : public AOCDay\n";
    out << "{\n";
    out << "public:\n";
    out << "    " << classStr << "() {}\n";
    out << "    ~" << classStr << "() {}\n";
    out << "    int Day() override { return " << day << "; }\n\n";
    out << "    uint64_t PartOne(File& f) override\n";
    out << "    {\n";
    out << "        return 0;\n";
    out << "    }\n\n";
    out << "    uint64_t PartTwo(File& f) override\n";
    out << "    {\n";
    out << "        return 0;\n";
    out << "    }\n";
    out << "};\n\n";
    out << "ADD_AOC_DAY(" << classStr << ");\n";

    out.close();

    std::ofstream input(inputPath);
    input.close();

    std::cout << "Generated:" << std::endl;
    std::cout << "  " << headerPath << std::endl;
    std::cout << "  " << inputPath << std::endl << std::endl;
    std::cout << "Remember to include `" << headerName << "`" << std::endl;
}

int main(int argc, char** argv)
{
    std::cout << "Advent of Code 2025 runner" << std::endl;
    std::cout << "©Ben Kyd 2025, All Rights Reserved" << std::endl;

    // Very shit command-line parsing :tm:
    int run_day = 0;
    std::filesystem::path base = "./";

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        // Day flag
        if (arg == "-d" || arg == "--day")
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

        if (arg == "-g" || arg == "--generate")
        {
            if (i + 1 >= argc)
            {
                std::cerr << "Error: -g requires a day number\n";
                return 1;
            }
            ++i;
            GenerateDay(std::atoi(argv[i]), base);
            return 1;
        }

        // Help flag
        if (arg == "help" || arg == "--help" || arg == "-h")
        {
            std::cout << "\nUsage:\n"
                      << "  -d [day]    Run a specific day\n"
                      << "  -p [path]   Set a base path for input\n"
                      << "  -g [day]    Generate a new day! (Stil need to add to compiler)\n"
                      << "  help        Show this help message\n"
                      << "  (no args)   Run all days\n";
            return 0;
        }

        // Unknown argument
        if (arg != "-d" && arg != "-p" && arg != "--path" &&
            arg != "help" && arg != "--help" && arg != "-h" &&
            arg != "-g" && arg != "--generate")
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
            File file1{path};

            uint64_t partOne = day->PartOne(file);
            int partTwo = day->PartTwo(file1);

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
            File file1{path};

            auto start = std::chrono::high_resolution_clock::now();

            uint64_t partOne = day->PartOne(file);

            auto endpart1 = std::chrono::high_resolution_clock::now();
            auto startpart2 = std::chrono::high_resolution_clock::now();

            uint64_t partTwo = day->PartTwo(file1);

            auto end = std::chrono::high_resolution_clock::now();

            std::cout << "Part 1: " << partOne << " - took " << std::chrono::duration<double, std::milli>(endpart1 - start).count() << "ms" << std::endl;
            std::cout << "Part 2: " << partTwo << " - took " << std::chrono::duration<double, std::milli>(end - startpart2).count() << "ms" << std::endl;
            std::cout << "Day " << run_day << " ran in " << std::chrono::duration<double, std::milli>(end - start).count() << "ms" << std::endl;
        }
    }

}

