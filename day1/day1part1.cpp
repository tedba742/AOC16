#include <fstream>
#include <string>
#include <iostream>
#include <cmath>  // For std::abs

struct Coordinates {
    int x;
    int y;
};

enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

// Function to get the new direction after a turn
Direction getNewDirection(Direction dir, char turn) {
    if (turn == 'L') {
        return (dir == NORTH) ? WEST : static_cast<Direction>(dir - 1);
    } else {  // turn == 'R'
        return (dir == WEST) ? NORTH : static_cast<Direction>(dir + 1);
    }
}

// Function to move in the current direction
void move(Coordinates &coord, Direction dir, int steps) {
    switch (dir) {
    case NORTH:
        coord.y += steps;
        break;
    case EAST:
        coord.x += steps;
        break;
    case SOUTH:
        coord.y -= steps;
        break;
    case WEST:
        coord.x -= steps;
        break;
    }
}

int main() {
    std::ifstream file{"input.txt"};
    std::string line;
    if (!std::getline(file, line)) {
        std::cerr << "Failed to read data from input.txt" << std::endl;
        return 1;
    }
    file.close();

    Coordinates currentLocation{0, 0};
    Direction currentDirection = NORTH;

    size_t i = 0;
    while (i < line.length()) {
        char turn = line[i++];
        int stepsStart = i;

        // Find the next comma or end of string to get steps
        while (i < line.length() && line[i] != ',') i++;
        int steps = std::stoi(line.substr(stepsStart, i - stepsStart));

        // Get new direction
        currentDirection = getNewDirection(currentDirection, turn);

        // Move in the current direction
        move(currentLocation, currentDirection, steps);

        // Skip comma and space if not at the end of the string
        if (i < line.length()) i += 2;
    }

    // Calculate the distance from the start
    int distanceFromStart = std::abs(currentLocation.x) + std::abs(currentLocation.y);
    std::cout << "Distance from start: " << distanceFromStart << std::endl;

    return 0;
}
