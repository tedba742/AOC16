#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cctype>

bool is_number(const std::string& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(),
             [s](char c) { return std::isdigit(c) || (c == '-' && s.size() > 1); });
}

int main() {
    std::map<char, int> registerMap;
    std::fstream file{"input.txt"};
    std::string line;
    std::vector<std::string> instructions;
    while (getline(file, line)) {
        instructions.push_back(line);
    }
    file.close();

    int i = 0;
    while (i < instructions.size()) {
        std::istringstream iss(instructions[i]);
        std::string command, src;
        char dest;

        iss >> command;
        if (command == "cpy") {
            iss >> src >> dest;
            if (is_number(src)) {
                registerMap[dest] = std::stoi(src);
            } else if (src.size() == 1 && std::isalpha(src[0])) {
                registerMap[dest] = registerMap[src[0]];
            }
        } else if (command == "inc") {
            iss >> dest;
            registerMap[dest]++;
        } else if (command == "dec") {
            iss >> dest;
            registerMap[dest]--;
        } else if (command == "jnz") {
            std::string x;
            int y;
            iss >> x >> y;
            int val = is_number(x) ? std::stoi(x) : registerMap[x[0]];
            if (val != 0) {
                i += y - 1;
            }
        }
        ++i;
    }

    for (const auto& reg : registerMap) {
        std::cout << "Register " << reg.first << " has value " << reg.second << std::endl;
    }

    return 0;
}
