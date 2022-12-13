// A bit ugly. Vectors would be easier, but stacks feel more appropriate.
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

int main()
{
    std::ifstream f("input05.txt");
    std::string line;
    std::getline(f, line);
    const int numStacks = int((line.length()+1)/4);
    std::vector<std::stack<char>> stacks1(numStacks);
    std::vector<std::stack<char>> stacks2(numStacks);
    {
        // Read the stacks (wrong order)
        std::vector<std::stack<char>> tempStacks(numStacks);
        do {
            for (int i = 0; i < numStacks; ++i) {
                if (char c = line.at(1 + i*4); c != ' ') { tempStacks.at(i).push(c); }
            }
        } while (std::getline(f, line) && (line.find('[') != std::string::npos));

        // Put them in the right order
        for (int i = 0; i < numStacks; ++i) {
            while (!tempStacks.at(i).empty()) {
                stacks1.at(i).push(tempStacks.at(i).top());
                stacks2.at(i).push(tempStacks.at(i).top());
                tempStacks.at(i).pop();
            }
        }
    }

    std::getline(f, line); // Empty line

    std::string ign;
    int move = 0;
    int from = 0;
    int to = 0;
    while (std::getline(f, line)) {
        std::istringstream iss(line);
        iss >> ign >> move >> ign >> from >> ign >> to;
        from--;
        to--;
        std::stack<char> temp;
        while (move-- > 0) {
            stacks1.at(to).push(stacks1.at(from).top());
            stacks1.at(from).pop();

            temp.push(stacks2.at(from).top());
            stacks2.at(from).pop();
        }

        while (!temp.empty()) {
            stacks2.at(to).push(temp.top());
            temp.pop();
        }
    }

    std::cout << "Part 1: ";
    for (auto& s : stacks1) { std::cout << s.top(); }
    std::cout << "\n";

    std::cout << "Part 2: ";
    for (auto& s : stacks2) { std::cout << s.top(); }
    std::cout << "\n";

    return 0;
}
