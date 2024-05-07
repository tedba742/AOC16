#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

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

    std::string line1, line2, line3;
    int validCount = 0;
    std::vector<Triangle> triangleVector;

    while (getline(file, line1) && getline(file, line2) && getline(file, line3)) {
        std::istringstream iss1(line1);
        std::istringstream iss2(line2);
        std::istringstream iss3(line3);
        int a1, a2, a3, b1, b2, b3, c1, c2, c3;

        iss1 >> a1 >> b1 >> c1;
        iss2 >> a2 >> b2 >> c2;
        iss3 >> a3 >> b3 >> c3;

        Triangle t1(a1, a2, a3);
        Triangle t2(b1, b2, b3);
        Triangle t3(c1, c2, c3);

        if (t1.isValid) validCount++;
        if (t2.isValid) validCount++;
        if (t3.isValid) validCount++;

        triangleVector.push_back(t1);
        triangleVector.push_back(t2);
        triangleVector.push_back(t3);
    }

    file.close();

    std::cout << "Number of valid triangles: " << validCount << std::endl;
    return 0;
}
