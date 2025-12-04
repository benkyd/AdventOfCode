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
        Grid(size_t h, size_t w) : data(h, std::vector<T>(w)) {}
        Grid(const std::vector<std::vector<T>>& d) : data(d) {}

        size_t Height() const { return data.size(); }
        size_t Width() const { return data.empty() ? 0 : data[0].size(); }

        const T& At(size_t r, size_t c) const { return data[r][c]; }

        const T* SafeAt(size_t r, size_t c) const
        {
            if (r >= Height() || c >= Width()) return nullptr;
            return &data[r][c];
        }

        void ReplaceAt(size_t r, size_t c, const T& value)
        {
            data[r][c] = value;
        }
        //
        // 4-neighbours (up, down, left, right)
        std::vector<const T*> Neighbours4(size_t r, size_t c, bool wrap = false) const
        {
            std::vector<const T*> out;

            auto H = Height();
            auto W = Width();

            auto idx = [&](size_t x, size_t limit) -> size_t {
                return wrap ? ((x + limit) % limit) : x;
            };

            if (r > 0 || wrap) out.push_back(&data[idx(r - 1, H)][c]);
            if (r + 1 < H || wrap) out.push_back(&data[idx(r + 1, H)][c]);
            if (c > 0 || wrap) out.push_back(&data[r][idx(c - 1, W)]);
            if (c + 1 < W || wrap) out.push_back(&data[r][idx(c + 1, W)]);

            return out;
        }

        // 8-neighbours (diagonals)
        std::vector<const T*> Neighbours8(size_t r, size_t c, bool wrap = false) const
        {
            std::vector<const T*> out;
            auto H = Height();
            auto W = Width();

            auto idx = [&](size_t x, size_t limit) -> size_t {
                return wrap ? ((x + limit) % limit) : x;
            };

            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    if (dr == 0 && dc == 0) continue;

                    size_t rr = r + dr;
                    size_t cc = c + dc;

                    if (!wrap) {
                        if (rr >= H || cc >= W) continue;
                    }

                    out.push_back(&data[idx(rr, H)][idx(cc, W)]);
                }
            }

            return out;
        }
    private:
        std::vector<std::vector<T>> data;
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
                std::vector<std::vector<T>> d;
                d.reserve(_lines.size());

                for (auto& line : _lines)
                {
                    std::vector<T> row;
                    row.reserve(line.size());

                    for (char ch : line)
                    {
                        if constexpr (std::is_constructible_v<T, char>)
                        {
                            row.emplace_back(T(ch));
                        }
                        else if constexpr (std::is_constructible_v<T, std::string_view>)
                        {
                            row.emplace_back(T(std::string_view(&ch, 1)));
                        }
                        else if constexpr (std::is_arithmetic_v<T>)
                        {
                            if (std::isdigit(ch))
                                row.emplace_back(T(ch - '0'));
                            else
                                throw std::runtime_error("Grid<T>: cannot convert character to numeric T");
                        }
                        else
                        {
                            static_assert(sizeof(T) == 0, "Grid<T>: T must be constructible from char or string_view");
                        }
                    }

                    d.push_back(std::move(row));
                }

                return Grid<T>(d);
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
