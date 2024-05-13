#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

int main() {
    std::string filename = "input.txt";
    std::ifstream file(filename);
    std::vector<std::pair<uint32_t, uint32_t>> ranges;

    if (!file) {
        std::cerr << "Unable to open file\n";
        return 1;
    }

    uint32_t start, end;
    char dash;
    std::string line;
    while (std::getline(file, line)) {
        std::sscanf(line.c_str(), "%u-%u", &start, &end);
        ranges.push_back({start, end});
    }
    file.close();

    std::sort(ranges.begin(), ranges.end());

    uint32_t currentStart = ranges[0].first, currentEnd = ranges[0].second;
    std::vector<std::pair<uint32_t, uint32_t>> mergedRanges;

    for (const auto& range : ranges) {
        if (range.first <= currentEnd + 1) {
            currentEnd = std::max(currentEnd, range.second);
        } else {
            mergedRanges.push_back({currentStart, currentEnd});
            currentStart = range.first;
            currentEnd = range.second;
        }
    }
    mergedRanges.push_back({currentStart, currentEnd});

    uint32_t lowestUnblockedIP = 0;
    if (mergedRanges[0].first > 0) {
        lowestUnblockedIP = 0;
    } else {
        for (const auto& range : mergedRanges) {
            if (range.first > lowestUnblockedIP + 1) {
                lowestUnblockedIP = currentEnd + 1;
                break;
            }
            currentEnd = range.second;
        }
    }

    std::cout << "The lowest unblocked IP is: " << lowestUnblockedIP << std::endl;
}
