#include <fstream>
#include <string>
#include <iostream>
#include <vector>

struct Coordinates {
    int x, y;
};

const int keypad[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

Coordinates move(Coordinates coord, char direction) {
    switch (direction) {
    case 'U':
        if (coord.y > 0) coord.y--;
        break;
    case 'R':
        if (coord.x < 2) coord.x++;
        break;
    case 'D':
        if (coord.y < 2) coord.y++;
        break;
    case 'L':
        if (coord.x > 0) coord.x--;
        break;
    }
    return coord;
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to read data from input.txt" << std::endl;
        return 1;
    }

    std::string line;
    Coordinates currentLocation = {1, 1};
    std::vector<int> code;

    while (getline(file, line)) {
        for (char &dir : line) {
            currentLocation = move(currentLocation, dir);
        }
        code.push_back(keypad[currentLocation.y][currentLocation.x]);
    }

    file.close();

    std::cout << "Bathroom code: ";
    for (int num : code) {
        std::cout << num;
    }
    std::cout << std::endl;

    return 0;
}
