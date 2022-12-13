#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>

// A "good enough" hash function for this task.
struct pairHash {
    inline std::size_t operator()(const std::pair<int, int>& v) const {
        return v.first*256*(v.second+1);
    }
};

auto main() -> int
{
    std::vector<std::vector<char>> forrest;
    std::string line;
    for (std::ifstream f("input08.txt"); std::getline(f, line); ) {
        std::vector<char> row;
        for (auto c : line) { row.push_back(c); }
        forrest.emplace_back(std::move(row));
    }
    const int w = forrest.at(0).size();
    const int h = forrest.size();

    std::unordered_set<std::pair<int, int>, pairHash> visible;
    // O(n^2) solution. Not great; not terrible.
    for (int y = 0; y < h; ++y) {
        char maxW = '0'-1; // View from West
        char maxE = '0'-1; // View from East
        auto& row = forrest.at(y);
        for (int x = 0; x < w; ++x) {
            if (char c = row.at(x); c > maxW)     { maxW = c; visible.insert({x,y}); }
            if (char c = row.at(w-x-1); c > maxE) { maxE = c; visible.insert({w-x-1,y});}
        }
    }
    for (int x = 0; x < w; ++x) {
        char maxN = '0'-1; // View from North
        char maxS = '0'-1; // View from South
        for (int y = 0; y < h; ++y) {
            if (char c = forrest.at(y).at(x); c > maxN)     { maxN = c; visible.insert({x,y}); }
            if (char c = forrest.at(h-y-1).at(x); c > maxS) { maxS = c; visible.insert({x,h-y-1}); }
        }
    }

    std::cout << "Part 1: " << visible.size() << "\n";


    int maxScenicScore = 0;
    // Lazy O(n^3) tree-by-tree solution. There are probably some more optimized ways to do this.
    for (int x = 1; x < w-1; ++x) {
        for (int y = 1; y < h-1; ++y) {
            char treeHeight = forrest.at(y).at(x);
            int scenicScore = 1;
            int d = 1;
            for (d = 1; (forrest.at(y+d).at(x) < treeHeight) && (y+d+1 < h); ++d) {}
            scenicScore *= d;
            for (d = 1; (forrest.at(y-d).at(x) < treeHeight) && (y-d-1 >= 0); ++d) {}
            scenicScore *= d;
            for (d = 1; (forrest.at(y).at(x+d) < treeHeight) && (x+d+1 < w); ++d) {}
            scenicScore *= d;
            for (d = 1; (forrest.at(y).at(x-d) < treeHeight) && (x-d-1 >= 0); ++d) {}
            scenicScore *= d;

            if (scenicScore > maxScenicScore) { maxScenicScore = scenicScore; }
        }
    }

    std::cout << "Part 2: " << maxScenicScore << "\n";

    return 0;
}
