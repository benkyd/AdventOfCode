CXX := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -I. -O3

TARGET := aoc
SRC := aoc.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
