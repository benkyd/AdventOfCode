#pragma once

#include <string>
#include <vector>
#include <filesystem>

struct FileFragment
{
    int Line,Col;
    std::string Data;
};

class File
{
public:
    // loads full file into memory RAII style
    // AS BLOB
    File(std::filesystem::path path);
    ~File();

    void SplitBy(char delim)
    {

    }

private:
    // Tokens are garunteed to be in-order
    std::vector<FileFragment> _tokens;

};

class AOCDay
{
    public:
        AOCDay();
        virtual ~AOCDay() = 0;

        virtual int PartOne(const File&) = 0;
        virtual int PartTwo(const File&) = 0;
};


