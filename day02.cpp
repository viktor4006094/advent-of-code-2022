// A very boring solution.

#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>

auto constexpr ROCK     = 1;
auto constexpr PAPER    = 2;
auto constexpr SCISSORS = 3;
auto constexpr WIN  = 6;
auto constexpr TIE  = 3;
auto constexpr LOSE = 0;

const std::unordered_map<std::string, int> strategy1 = {
    { "A X", ROCK + TIE },
    { "B X", ROCK + LOSE },
    { "C X", ROCK + WIN },
    { "A Y", PAPER + WIN },
    { "B Y", PAPER + TIE },
    { "C Y", PAPER + LOSE },
    { "A Z", SCISSORS + LOSE },
    { "B Z", SCISSORS + WIN },
    { "C Z", SCISSORS + TIE },
};

const std::unordered_map<std::string, int> strategy2 = {
    { "A X", LOSE + SCISSORS },
    { "B X", LOSE + ROCK },
    { "C X", LOSE + PAPER },
    { "A Y", TIE + ROCK },
    { "B Y", TIE + PAPER },
    { "C Y", TIE + SCISSORS },
    { "A Z", WIN + PAPER },
    { "B Z", WIN + SCISSORS },
    { "C Z", WIN + ROCK },
};

int main()
{
    int score1 = 0;
    int score2 = 0;
    std::string line;
    std::ifstream f("input02.txt");
    while (std::getline(f, line)) {
        score1 += strategy1.at(line);
        score2 += strategy2.at(line);
    }

    std::cout << "Part 1: Score: " << score1 << '\n';
    std::cout << "Part 2: Score: " << score2 << '\n';

    return 0;
}
