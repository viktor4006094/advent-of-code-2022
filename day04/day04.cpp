#include <fstream>
#include <iostream>
#include <sstream>

int main()
{
    int count1 = 0;
    int count2 = 0;
    int minA = 0;
    int maxA = 0;
    int minB = 0;
    int maxB = 0;
    std::string line;
    for (std::ifstream f("input04.txt"); getline(f, line);) {
        char delim;
        std::istringstream iss(line);
        iss >> minA >> delim >> maxA >> delim >> minB >> delim >> maxB;

        if ((minA <= minB && maxB <= maxA) || (minB <= minA && maxA <= maxB)) {
            count1++;
        }
        if (!(minA > maxB || minB > maxA)) {
            count2++;
        }
    }
    std::cout << "Part 1: " << count1 << "\n";
    std::cout << "Part 2: " << count2 << "\n";

    return 1;
}
