#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

struct Triangle {
    int x, y, z;
    bool isValid;

    Triangle(int x, int y, int z) : x(x), y(y), z(z) {
        isValid = (x + y > z) && (x + z > y) && (y + z > x);
    }
};

int main() {
    std::fstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }

    std::string line;
    int validCount = 0;

    while (getline(file, line)) {
        std::istringstream iss(line);
        int x, y, z;
        if (iss >> x >> y >> z) {
            Triangle triangle(x, y, z);
            if (triangle.isValid) {
                validCount++;
            }
        }
    }

    file.close();

    std::cout << "Number of valid triangles: " << validCount << std::endl;
    return 0;
}
