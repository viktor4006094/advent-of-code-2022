// Bad and lazy solution.
#include <fstream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <limits>

template <typename T, typename _>
auto contains(std::unordered_map<T, _>& set, T val) -> bool
{
    return (set.find(val) != set.end());
}

struct Directory {
    Directory(std::shared_ptr<Directory> p = nullptr) : parent(p) { }

    size_t fileSizeSum = 0;
    std::shared_ptr<Directory> parent;
    std::unordered_map<std::string, std::shared_ptr<Directory>> subDirectories;
};

constexpr auto sizeLimit = 100'000;
// Using globals is lazy, I know.
size_t sumSize = 0;
std::vector<size_t> allDirSizes;

auto calcDirSize(std::shared_ptr<Directory> dir) -> size_t
{
    size_t size = dir->fileSizeSum;
    for (auto& [n, d] : dir->subDirectories) {
        size += calcDirSize(d);
    }
    if (size <= sizeLimit) { sumSize += size; }
    allDirSizes.push_back(size);
    return size;
}

// Zero safety checks.
auto main() -> int
{
    std::ifstream f("input07.txt");
    std::string line;

    getline(f, line); 
    std::shared_ptr<Directory> head = std::make_shared<Directory>();
    std::shared_ptr<Directory> current = head;

    // Get info from output
    while (getline(f, line)) {
        if (line.substr(0, 6) == "$ cd /") {
            current = head;
        } else if (line.substr(0, 7) == "$ cd ..") {
            if (!current->parent) { return 0; }
            current = current->parent;
        } else if (line.substr(0, 5) == "$ cd ") {
            std::string dirName = line.substr(5);
            if (!contains(current->subDirectories, dirName)) {
                current->subDirectories[dirName] = std::make_shared<Directory>(current);
            }
            current = current->subDirectories[dirName];
        } else if (line.substr(0,4) == "$ ls") {
            current->fileSizeSum = 0;
        } else if (line.substr(0, 4) != "dir ") {
            current->fileSizeSum += std::stoi(line);
        }
    }

    auto fullSize = calcDirSize(head);
    std::cout << "Part 1: " << sumSize << "\n";

    auto freeSize = 70'000'000 - fullSize;
    auto toDelete = 30'000'000 - freeSize;

    size_t dirToDeleteSize = std::numeric_limits<size_t>::max();
    for (auto s : allDirSizes) {
        if (s >= toDelete && s < dirToDeleteSize) { dirToDeleteSize = s; }
    }

    std::cout << "Part 2: " << dirToDeleteSize << "\n";

    return 0;
}
