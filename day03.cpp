#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

// It's pretty dumb that set::contains() isn't a thing pre C++20
template <typename T>
bool setContains(std::unordered_set<T>& set, T val) {
    return (set.find(val) != set.end());
}

int main()
{
    int prioSum = 0;
    std::string line;
    for (std::ifstream f("input03.txt"); std::getline(f, line);) {
        auto mid = std::next(line.begin(), line.size()/2);
        std::unordered_set<char> left(line.begin(), mid);
        std::unordered_set<char> right(mid, line.end());

        for (auto c : left) {
            if (setContains(right, c)) {
                // prioSum += (c > 'Z') ? int(c - 'a') + 1 : int(c - 'A') + 27; // boring
                prioSum += (int(c - 'A') + 27) % 58; // fun
            }
        }
    }

    std::cout << "Part 1: " << prioSum << '\n';

    prioSum = 0;
    std::string elf1;
    std::string elf2;
    std::string elf3;
    for (std::ifstream f("input03.txt"); std::getline(f, elf1);) {
        std::getline(f, elf2);
        std::getline(f, elf3);
        std::unordered_set<char> chars1(elf1.begin(), elf1.end());
        std::unordered_set<char> chars2(elf2.begin(), elf2.end());
        std::unordered_set<char> chars3(elf3.begin(), elf3.end());

        for (auto c : chars1) {
            if (setContains(chars2, c) && setContains(chars3, c)) {
                prioSum += (int(c - 'A') + 27) % 58;
                break;
            }
        }
    }

    std::cout << "Part 2: " << prioSum << '\n';

    return 0;
}
