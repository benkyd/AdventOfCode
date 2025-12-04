#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

template<typename T>
class Grid
{
public:
    Grid() = default;

    Grid(size_t h, size_t w) : height(h), width(w), data(h * w) {}

    Grid(const std::vector<T> d)
        : height(d.size())
        , width(d.empty() ? 0 : d[0].size())
        , data(d) {}

    size_t Height() const { return height; }
    size_t Width() const { return width; }

    const T& At(size_t r, size_t c) const
    {
        return data[r * width + c];
    }

    const T* SafeAt(size_t r, size_t c) const
    {
        if (r >= height || c >= width) return nullptr;
        return &data[r * width + c];
    }

    void ReplaceAt(size_t r, size_t c, const T& value)
    {
        data[r * width + c] = value;
    }

    size_t Neighbours4(size_t r, size_t c, const T* out[4], bool wrap = false) const
    {
        size_t count = 0;

        if (wrap)
        {
            out[count++] = &data[((r - 1 + height) % height) * width + c];
            out[count++] = &data[((r + 1) % height) * width + c];
            out[count++] = &data[r * width + ((c - 1 + width) % width)];
            out[count++] = &data[r * width + ((c + 1) % width)];
        } else
        {
            if (r > 0)
                out[count++] = &data[(r - 1) * width + c];
            if (r + 1 < height)
                out[count++] = &data[(r + 1) * width + c];
            if (c > 0)
                out[count++] = &data[r * width + (c - 1)];
            if (c + 1 < width)
                out[count++] = &data[r * width + (c + 1)];
        }

        return count;
    }

    size_t Neighbours8(size_t r, size_t c, const T* out[8], bool wrap = false) const
    {
        size_t count = 0;

        if (wrap) {
            for (int dr = -1; dr <= 1; ++dr)
            {
                for (int dc = -1; dc <= 1; ++dc)
                {
                    if (dr == 0 && dc == 0) continue;

                    size_t rr = (r + dr + height) % height;
                    size_t cc = (c + dc + width) % width;
                    out[count++] = &data[rr * width + cc];
                }
            }
        } else {
            for (int dr = -1; dr <= 1; ++dr)
            {
                for (int dc = -1; dc <= 1; ++dc)
                {
                    if (dr == 0 && dc == 0) continue;

                    size_t rr = r + dr;
                    size_t cc = c + dc;

                    if (rr >= height || cc >= width) continue;

                    out[count++] = &data[rr * width + cc];
                }
            }
        }

        return count;
    }

private:
    size_t height = 0;
    size_t width = 0;
    std::vector<T> data;
};


struct FileFragment
{
    int Line, Col;
    std::string Data;
};

inline std::pair<FileFragment, FileFragment> SplitToken(std::string del)
{

}

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

        void SplitByIndex(const int index)
        {
            _tokens.clear();
            _tokens.reserve(_lines.size());

            for (size_t lineIndex = 0; lineIndex < _lines.size(); ++lineIndex)
            {
                const auto& line = _lines[lineIndex];
                std::vector<FileFragment> lineTokens;

                // Bounds check
                if (index < 0 || static_cast<size_t>(index) >= line.size())
                {
                    // Just return whole line as single token if index is out of range
                    lineTokens.push_back({
                            static_cast<int>(lineIndex + 1),
                            0,
                            line
                            });
                }
                else
                {
                    // Left part (may be empty, e.g. index = 0)
                    lineTokens.push_back({
                            static_cast<int>(lineIndex + 1),
                            0,
                            line.substr(0, index)
                            });

                    // Right part (may be empty)
                    lineTokens.push_back({
                            static_cast<int>(lineIndex + 1),
                            1,
                            line.substr(index)
                            });
                }

                _tokens.push_back(std::move(lineTokens));
            }
        }

        /// Access tokens for a given line (1-based)
        const std::vector<FileFragment>& TokensForLine(int line) const
        {
            if (line < 0 || line > static_cast<int>(_tokens.size()))
            {
                static const std::vector<FileFragment> empty;
                return empty;
            }
            return _tokens[line];
        }

        // Access a chunk of tokens for a given line
        // E.g. Iterate [1,2], [2,3], [3,4]
        std::vector<std::vector<FileFragment>> ChunkView(int line, size_t size, size_t stride)
        {
            const auto& v = _tokens[line];
            std::vector<std::vector<FileFragment>> chunks;

            if (v.empty() || stride == 0)
                return chunks;

            for (size_t i = 0; i + size <= v.size(); i += stride)
            {
                std::cout << "max " << i + size << " tokens " << v.size() << " index " << i << " size " << size << " stride " << stride << std::endl;
                chunks.emplace_back(v.begin() + i, v.begin() + i + size);
            }

            return chunks;
        }


        template<typename T>
            Grid<T> AsGrid() const
            {
                const size_t height = _lines.size();
                if (height == 0) return Grid<T>(0, 0);

                const size_t width = _lines[0].size();

                Grid<T> grid(height, width);

                for (size_t r = 0; r < height; ++r)
                {
                    const auto& line = _lines[r];
                    for (size_t c = 0; c < width; ++c)
                    {
                        char ch = line[c];

                        if constexpr (std::is_constructible_v<T, char>)
                        {
                            grid.ReplaceAt(r, c, T(ch));
                        }
                        else if constexpr (std::is_constructible_v<T, std::string_view>)
                        {
                            grid.ReplaceAt(r, c, T(std::string_view(&ch, 1)));
                        }
                        else if constexpr (std::is_arithmetic_v<T>)
                        {
                            if (std::isdigit(ch))
                                grid.ReplaceAt(r, c, T(ch - '0'));
                            else
                                throw std::runtime_error("Grid<T>: cannot convert character to numeric T");
                        }
                        else
                        {
                            static_assert(sizeof(T) == 0, "Grid<T>: T must be constructible from char or string_view");
                        }
                    }
                }

                return grid;
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

        virtual uint64_t PartOne(File&) = 0;
        virtual uint64_t PartTwo(File&) = 0;
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
