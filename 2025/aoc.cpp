
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <vector>

#include "aoc.hpp"
#include "day1.hpp"
#include "day2.hpp"
#include "day3.hpp"
#include "day4.hpp"

void GenerateDay(int day, std::filesystem::path base)
{
    std::cout << "Generating template for day " << day << std::endl;
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
    int num_runs = 1;
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

        // Runs flag
        if (arg == "-r" || arg == "--runs")
        {
            if (i + 1 >= argc)
            {
                std::cerr << "Error: -r requires a number of runs\n";
                return 1;
            }
            ++i;
            num_runs = std::atoi(argv[i]);
            if (num_runs < 1) num_runs = 1;
            std::cout << "Number of runs for averaging: " << num_runs << "\n";
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
                      << "  -r [runs]   Number of runs to average timings (default: 1)\n"
                      << "  -p [path]   Set a base path for input\n"
                      << "  -g [day]    Generate a new day! (Still need to add to compiler)\n"
                      << "  help        Show this help message\n"
                      << "  (no args)   Run all days\n";
            return 0;
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
            uint64_t partTwo = day->PartTwo(file1);

            std::cout << "Part 1: " << partOne << "\n";
            std::cout << "Part 2: " << partTwo << "\n";
        }
    }
    else
    {
        for (auto& [num, day] : GetRegisteredDays(run_day))
        {
            std::cout << "Running Day " << num;
            if (num_runs > 1) {
                std::cout << " (averaging over " << num_runs << " runs)";
            }
            std::cout << ":\n";

            std::string filename = std::to_string(num) + ".txt";
            std::filesystem::path path = base / filename;

            std::cout << "Reading " << path << "..." << std::endl;

            // Storage for timing results
            std::vector<double> part1_times;
            std::vector<double> part2_times;
            std::vector<double> total_times;

            part1_times.reserve(num_runs);
            part2_times.reserve(num_runs);
            total_times.reserve(num_runs);

            uint64_t partOne = 0;
            uint64_t partTwo = 0;

            // Run multiple times
            for (int run = 0; run < num_runs; ++run)
            {
                File file{path};
                File file1{path};

                auto start = std::chrono::high_resolution_clock::now();

                partOne = day->PartOne(file);

                auto endpart1 = std::chrono::high_resolution_clock::now();
                auto startpart2 = std::chrono::high_resolution_clock::now();

                partTwo = day->PartTwo(file1);

                auto end = std::chrono::high_resolution_clock::now();

                part1_times.push_back(std::chrono::duration<double, std::milli>(endpart1 - start).count());
                part2_times.push_back(std::chrono::duration<double, std::milli>(end - startpart2).count());
                total_times.push_back(std::chrono::duration<double, std::milli>(end - start).count());
            }

            // Calculate averages
            double p1_avg = std::accumulate(part1_times.begin(), part1_times.end(), 0.0) / num_runs;
            double p2_avg = std::accumulate(part2_times.begin(), part2_times.end(), 0.0) / num_runs;
            double total_avg = std::accumulate(total_times.begin(), total_times.end(), 0.0) / num_runs;

            // Print results
            std::cout << "Part 1: " << partOne << " - took "
                      << std::fixed << std::setprecision(3) << p1_avg << "ms" << std::endl;
            std::cout << "Part 2: " << partTwo << " - took "
                      << std::fixed << std::setprecision(3) << p2_avg << "ms" << std::endl;
            std::cout << "Day " << run_day << " ran in "
                      << std::fixed << std::setprecision(3) << total_avg << "ms" << std::endl;
        }
    }
}

