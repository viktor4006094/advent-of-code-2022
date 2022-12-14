#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

auto sign(int x) -> int { return (x > 0) - (0 > x); } // not exactly readable, but it looks cool!

struct Position {
    int x = 0;
    int y = 0;

    auto operator+(const Position& other) -> Position&
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    auto operator+=(const Position& other) -> Position&
    {
        x += other.x;
        y += other.y;
        return *this;
    }
};

inline bool operator==(const Position& l, const Position& r) { return (l.x == r.x) && (l.y == r.y); }
inline bool operator!=(const Position& l, const Position& r) { return !(l==r); }

namespace std {
    template<> struct hash<Position> {
        std::size_t operator()(const Position& p) const noexcept
        {
            return p.x*1024+(p.y);
        }
    };
}

auto follow(Position& tail, const Position& head) -> void
{
    Position dist{head.x-tail.x, head.y-tail.y};
    Position dir{sign(dist.x), sign(dist.y)};

    if (dist!=dir) { tail+=dir; }
}

auto main() -> int
{
    const std::unordered_map<char, Position> directions = {
        {'R', { 1, 0}},
        {'L', {-1, 0}},
        {'U', { 0,-1}},
        {'D', { 0, 1}},
    };
    std::unordered_set<Position> visited;
    std::string line;

    Position head = {0,0};
    Position tail = {0,0};
    for (std::ifstream f("input09.txt"); std::getline(f, line);) {
        auto& dir = directions.at(line.at(0));
        int steps = std::stoi(line.substr(2));
        while (steps-->0) {
            head += dir;
            follow(tail, head);
            visited.insert(tail);
        }
    }

    std::cout << "Part 1: " << visited.size() << "\n";

    visited.clear();
    constexpr int kLength = 10;
    std::array<Position, kLength> rope;
    for (std::ifstream f("input09.txt"); std::getline(f, line);) {
        auto& dir = directions.at(line.at(0));
        int steps = std::stoi(line.substr(2));
        while (steps-->0) {
            rope.at(0) += dir;
            for (int i = 1; i < kLength; ++i) {
                follow(rope.at(i), rope.at(i-1));
            }
            visited.insert(rope.at(9));
        }
    }

    std::cout << "Part 2: " << visited.size() << "\n";

    return 0;
}
