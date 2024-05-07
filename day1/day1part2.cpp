#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <set>

struct Coordinates {
    int x, y;
};

// Custom comparator for using Coordinates in a set
struct CompareCoordinates {
    bool operator() (const Coordinates& a, const Coordinates& b) const {
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    }
};

enum Direction {
    NORTH, EAST, SOUTH, WEST
};

Direction getNewDirection(Direction dir, char turn) {
    if (turn == 'L') {
        return (dir == NORTH) ? WEST : static_cast<Direction>(dir - 1);
    } else {  // turn == 'R'
        return (dir == WEST) ? NORTH : static_cast<Direction>(dir + 1);
    }
}

void move(Coordinates &coord, Direction dir, int steps, std::set<Coordinates, CompareCoordinates>& visited, Coordinates& firstDuplicate, bool& foundDuplicate) {
    for (int i = 0; i < steps; ++i) {
        switch (dir) {
        case NORTH:
            coord.y++;
            break;
        case EAST:
            coord.x++;
            break;
        case SOUTH:
            coord.y--;
            break;
        case WEST:
            coord.x--;
            break;
        }
        // Check for duplicates during each step
        if (!visited.insert(coord).second) {
            firstDuplicate = coord;
            foundDuplicate = true;
            return;
        }
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
    Coordinates firstDuplicate;
    bool foundDuplicate = false;
    Direction currentDirection = NORTH;
    std::set<Coordinates, CompareCoordinates> visited;  // Set to track visited locations
    visited.insert(currentLocation);  // Start location is considered visited

    size_t i = 0;
    while (i < line.length()) {
        char turn = line[i++];
        int stepsStart = i;

        while (i < line.length() && line[i] != ',') i++;
        int steps = std::stoi(line.substr(stepsStart, i - stepsStart));

        currentDirection = getNewDirection(currentDirection, turn);

        move(currentLocation, currentDirection, steps, visited, firstDuplicate, foundDuplicate);

        if (foundDuplicate) break;

        if (i < line.length()) i += 2;
    }

    int distanceFromStart = std::abs(currentLocation.x) + std::abs(currentLocation.y);
    std::cout << "Distance from start: " << distanceFromStart << std::endl;

    if (foundDuplicate) {
        std::cout << "First duplicate location found at: (" << firstDuplicate.x << ", " << firstDuplicate.y << ")" << std::endl;
        int duplicateDistance = std::abs(firstDuplicate.x) + std::abs(firstDuplicate.y);
        std::cout << "Distance from start to first duplicate: " << duplicateDistance << std::endl;
    } else {
        std::cout << "No duplicate locations found." << std::endl;
    }

    return 0;
}
