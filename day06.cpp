#include <fstream>
#include <iostream>
#include <unordered_map>

auto main() -> int
{
    std::string datastream;
    std::getline(std::ifstream("input06.txt"), datastream);

    size_t markerStart = 0;
    size_t msgLength = datastream.length();
    for (size_t i = 3; i < msgLength; ++i) {
        auto a = datastream.at(i-3);
        auto b = datastream.at(i-2);
        auto c = datastream.at(i-1);
        auto d = datastream.at(i);
        if (a!=b && a!=c && a!=d && b!=c && b!=d && c!=d) {
            markerStart = i+1;
            break;
        }
    }

    std::cout << "Part 1: " << markerStart << "\n";

    constexpr auto kMsgMarkerLen = 14;
    size_t msgStart = 0;
    std::unordered_map<char, int> runningCount;
     for (size_t i = 0; i < msgLength; ++i) {
        if (runningCount.size() == kMsgMarkerLen) {
            msgStart = i;
            break;
        }
        runningCount[datastream.at(i)]++;
        if (i < kMsgMarkerLen) {
            continue; 
        } else if (runningCount[datastream.at(i-kMsgMarkerLen)] > 1) {
            runningCount[datastream.at(i-kMsgMarkerLen)]--;
        } else {
            runningCount.erase(datastream.at(i-kMsgMarkerLen));
        }
    }

    std::cout << "Part 2: " << msgStart << "\n";

    return 0;
}
