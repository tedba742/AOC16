#include <fstream>
#include <string>
#include <iostream>

bool containsABBA(const std::string& s) {
    for (int i = 0; i < s.length() - 3; ++i) {
        if (s[i] == s[i+3] && s[i+1] == s[i+2] && s[i] != s[i+1]) {
            return true;
        }
    }
    return false;
}

int main() {
    std::fstream file{"input.txt"};
    std::string line;
    int tlsCount = 0;

    while (getline(file, line)) {
        bool hasABBAOutside {false};
        bool hasABBAInside {false};
        std::string temp{""};
        bool insideBrackets = {false};

        for (int i = 0; i < line.length(); ++i) {
            if (line[i] == '[') {
                if (!insideBrackets && containsABBA(temp)) {
                    hasABBAOutside = true;
                }
                temp = "";
                insideBrackets = true;
            } else if (line[i] == ']') {
                if (insideBrackets && containsABBA(temp)) {
                    hasABBAInside = true;
                }
                temp = "";
                insideBrackets = false;
            } else {
                temp += line[i];
            }
        }

        if (!insideBrackets && containsABBA(temp)) {
            hasABBAOutside = true;
        }

        if (hasABBAOutside && !hasABBAInside) {
            tlsCount++;
        }
    }

    file.close();
    std::cout << "Number of IPs supporting TLS: " << tlsCount << std::endl;
    return 0;
}
