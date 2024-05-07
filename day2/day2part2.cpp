#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

struct Coordinates {
    int x, y;
};

const char keypad[5][5] = {
    {'-', '-', '1', '-', '-'},
    {'-', '2', '3', '4', '-'},
    {'5', '6', '7', '8', '9'},
    {'-', 'A', 'B', 'C', '-'},
    {'-', '-', 'D', '-', '-'}
};

bool isValid(const Coordinates& coord) {
    if (coord.x < 0 || coord.x >= 5 || coord.y < 0 || coord.y >= 5) return false;
    return keypad[coord.y][coord.x] != '-';
}

Coordinates move(Coordinates coord, char direction) {
    Coordinates newCoord = coord;
    switch (direction) {
    case 'U':
        newCoord.y--;
        break;
    case 'R':
        newCoord.x++;
        break;
    case 'D':
        newCoord.y++;
        break;
    case 'L':
        newCoord.x--;
        break;
    }
    return isValid(newCoord) ? newCoord : coord;
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to read data from input.txt" << std::endl;
        return 1;
    }

    std::string line;
    Coordinates currentLocation = {0, 2};
    std::string code;

    while (getline(file, line)) {
        for (char &dir : line) {
            currentLocation = move(currentLocation, dir);
        }
        code.push_back(keypad[currentLocation.y][currentLocation.x]);
    }

    file.close();

    std::cout << "Bathroom code: " << code << std::endl;

    return 0;
}
