#include <fstream>
#include <string>
#include <iostream>

int main() {
    std::fstream file{"input.txt"};
    std::string line{""};
    int decompressedLength {0};

    while (getline(file, line)) {
        for (size_t i = 0; i < line.size(); i++) {
            if (line[i] == '(') {
                std::size_t bracketPos = line.find(")", i);
                if (bracketPos != std::string::npos) {
                    std::string multiplicationString = line.substr(i + 1, bracketPos - (i + 1));
                    int a, b;
                    sscanf(multiplicationString.c_str(), "%dx%d", &a, &b);

                    if (i + 1 + multiplicationString.length() + 1 + a <= line.size()) {
                        std::string sequenceToMultiply = line.substr(bracketPos + 1, a);
                        decompressedLength += a * b;
                        i = bracketPos + a;
                    }
                }
            } else {
                decompressedLength++;
            }
        }
    }

    file.close();
    std::cout << "Total decompressed length: " << decompressedLength << std::endl;
    return 0;
}
