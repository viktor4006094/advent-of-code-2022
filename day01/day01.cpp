#include <fstream>
#include <iostream>
#include <numeric>
#include <set>

// Part 1
int topOneCal()
{
    int cal = 0;
    int calMax = 0;
    std::string line = "";

    for (std::ifstream f("input01.txt"); std::getline(f, line);) {
        if (line == "") {
            if (cal > calMax) { calMax = cal; }
            cal = 0;
        } else {
            cal += std::stoi(line);
        }
    }
    if (cal > calMax) { calMax = cal; }
    return calMax;
}

// Part 2
int topThreeCal()
{
    std::multiset<int, std::greater<int>> calSorted;
    int cal = 0;
    std::string line = "";

    for (std::ifstream f("input01.txt"); std::getline(f, line);) {
        if (line == "") {
            calSorted.insert(cal);
            cal = 0;
        } else {
            cal += std::stoi(line);
        }
    }
    calSorted.insert(cal);
    return std::reduce(calSorted.begin(), std::next(calSorted.begin(), 3));
}

int main()
{
    std::cout << "Part 1: " << topOneCal() << " calories\n";
    std::cout << "Part 2: " << topThreeCal() << " calories\n";
    return 1;
}