#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

struct FileFragment
{
    int Line, Col;
    std::string Data;
};

class File
{
public:
    File() = default;

    explicit File(const std::filesystem::path& path)
    {
        Load(path);
    }

    void Load(const std::filesystem::path& path)
    {
        if (!std::filesystem::exists(path))
        {
            throw std::runtime_error("File " + path.string() + " does not exist");
        }

        std::ifstream file(path.string());
        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open file " + path.string());
        }

        _lines.clear();
        std::string line;
        while (std::getline(file, line))
        {
            _lines.push_back(line);
        }
    }

    /// Split each line by a multi-character delimiter
    void SplitBy(const std::string& delim)
    {
        _tokens.clear();

        for (size_t lineIndex = 0; lineIndex < _lines.size(); ++lineIndex)
        {
            const auto& line = _lines[lineIndex];
            std::vector<FileFragment> lineTokens;

            size_t start = 0;
            int colIndex = 0;

            while (true) {
                size_t pos = line.find(delim, start);
                if (pos == std::string::npos)
                {
                    lineTokens.push_back({
                            static_cast<int>(lineIndex + 1),
                            colIndex,
                            line.substr(start)
                            });
                    break;
                }

                lineTokens.push_back({
                        static_cast<int>(lineIndex + 1),
                        colIndex,
                        line.substr(start, pos - start)
                        });

                start = pos + delim.size();
                ++colIndex;
            }

            _tokens.push_back(std::move(lineTokens));
        }
    }


    /// Access tokens for a given line (1-based)
    const std::vector<FileFragment>& TokensForLine(int line) const
    {
        if (line < 1 || line > static_cast<int>(_tokens.size()))
        {
            static const std::vector<FileFragment> empty;
            return empty;
        }
        return _tokens[line - 1];
    }

    /// Iterate through all lines and their tokens
    auto begin() const { return _tokens.begin(); }
    auto end() const { return _tokens.end(); }

    /// Access raw lines (before splitting)
    const std::vector<std::string>& Lines() const { return _lines; }

private:
    std::vector<std::string> _lines;
    std::vector<std::vector<FileFragment>> _tokens;  // [line][token]
};

class AOCDay
{
    public:
        // The "driver" will expect the Name
        // to have the same string as the input
        // return 1 -> 1.txt
        virtual int Day() = 0;

        virtual int PartOne(File&) = 0;
        virtual int PartTwo(File&) = 0;
};

inline std::unordered_map<int, AOCDay*>& GetRegisteredDays(int day = 0)
{
    static std::unordered_map<int, AOCDay*> days;

    if (day != 0)
    {
        static std::unordered_map<int, AOCDay*> single;
        single.clear();
        auto it = days.find(day);
        if (it != days.end())
            single[day] = it->second;
        else
            std::cerr << "Warning: requested day " << day << " not found.\n";
        return single;
    }

    return days;
}

template<typename T>
struct AOCDayRegistrar
{
    AOCDayRegistrar()
    {
        auto* instance = new T();
        int day = instance->Day();

        auto& days = GetRegisteredDays();
        if (days.count(day))
        {
            std::cerr << "Duplicate registration for day " << day << "\n";
            delete instance;
            return;
        }

        days[day] = instance;
    }
};

#define ADD_AOC_DAY(DAYCLASS) \
    static AOCDayRegistrar<DAYCLASS> DAYCLASS##_registrar_instance;
