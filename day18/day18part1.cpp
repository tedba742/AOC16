#include <iostream>
#include <string>
#include <vector>

std::string getNextRow(const std::string& currentRow) {
    std::string nextRow = "";
    int n = currentRow.size();

    for (int i = 0; i < n; ++i) {
        char left = (i > 0) ? currentRow[i - 1] : '.';
        char center = currentRow[i];
        char right = (i < n - 1) ? currentRow[i + 1] : '.';

        if ((left == '^' && center == '^' && right == '.') ||
            (left == '.' && center == '^' && right == '^') ||
            (left == '^' && center == '.' && right == '.') ||
            (left == '.' && center == '.' && right == '^')) {
            nextRow += '^';
        } else {
            nextRow += '.';
        }
    }

    return nextRow;
}

int main() {
    std::string firstRow = "^.^^^.^..^....^^....^^^^.^^.^...^^.^.^^.^^.^^..^.^...^.^..^.^^.^..^.....^^^.^.^^^..^^...^^^...^...^.";
    int totalRows = 40;
    int safeCount = 0;
    std::vector<std::string> map;
    map.push_back(firstRow);

    for (char c : firstRow) {
        if (c == '.') ++safeCount;
    }

    for (int row = 1; row < totalRows; ++row) {
        std::string nextRow = getNextRow(map[row - 1]);
        map.push_back(nextRow);
        for (char c : nextRow) {
            if (c == '.') ++safeCount;
        }
    }

    std::cout << "Total number of safe tiles in " << totalRows << " rows: " << safeCount << std::endl;
}
