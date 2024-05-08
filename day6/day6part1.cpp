#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <limits>

int main() {
    std::fstream file{"input.txt"};
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }

    std::string line;
    std::map<int, std::map<char, int>> charCount;

    while (getline(file, line)) {
        for (size_t i = 0; i < line.size(); ++i) {
            char c = line[i];
            charCount[i][c]++;
        }
    }

    file.close();
    std::string result{""};
    for (const auto& idx_map : charCount) {
        int maxCount = std::numeric_limits<int>::min();
        char maxChar = 0;
        for (const auto& pair : idx_map.second) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                maxChar = pair.first;
            }
        }
        result += maxChar;

    }
    
    std::cout << "Column " << result << std::endl;
}
