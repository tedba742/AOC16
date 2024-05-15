#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

struct Disc {
    int positions;
    int startPosition;
};

bool canPassThroughAllDiscs(const std::vector<Disc>& discs, int startTime) {
    for (int i = 0; i < discs.size(); ++i) {
        int positionAtTime = (discs[i].startPosition + startTime + i + 1) % discs[i].positions;
        if (positionAtTime != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    std::vector<Disc> discs = {
        {17, 1},
        {7, 0},
        {19, 2},
        {5, 0},
        {3, 0},
        {13, 5},
        {11, 0}
    };

    int time = 0;
    while (!canPassThroughAllDiscs(discs, time)) {
        time++;
    }

    std::cout << "The first time to press the button is: " << time << std::endl;
    return 0;
}
