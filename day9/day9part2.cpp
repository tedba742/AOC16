#include <fstream>
#include <string>
#include <iostream>

long long decompressedLength(const std::string& line, int start, int end) {
    long long length = 0;
    for (int i = start; i < end; ++i) {
        if (line[i] == '(') {
            size_t bracketPos = line.find(")", i);
            if (bracketPos != std::string::npos) {
                std::string marker = line.substr(i + 1, bracketPos - (i + 1));
                int chars, repeat;
                sscanf(marker.c_str(), "%dx%d", &chars, &repeat);

                int nextSectionStart = bracketPos + 1;
                int nextSectionEnd = nextSectionStart + chars;

                if (nextSectionEnd <= end) {
                    long long sectionLength = decompressedLength(line, nextSectionStart, nextSectionEnd);
                    length += sectionLength * repeat;
                    i = nextSectionEnd - 1;
                }
            }
        } else {
            length++;
        }
    }
    return length;
}

int main() {
    std::fstream file{"input.txt"};
    std::string line;
    long long totalDecompressedLength = 0;

    while (getline(file, line)) {
        totalDecompressedLength += decompressedLength(line, 0, line.length());
    }

    file.close();
    std::cout << "Total decompressed length: " << totalDecompressedLength << std::endl;
    return 0;
}
