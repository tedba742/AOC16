#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

struct Room {
    std::string roomName;
    int sectorID;
    std::string checkLetters;
    bool isValid;

    Room(const std::string& name, int id, const std::string& checksum) :
        roomName(name), sectorID(id), checkLetters(checksum) {
        isValid = checkValidity();
    }

    bool checkValidity() {
        std::map<char, int> frequency;
        for (char c : roomName) {
            if (c != '-')
                frequency[c]++;
        }

        std::vector<std::pair<char, int>> vec(frequency.begin(), frequency.end());
        std::sort(vec.begin(), vec.end(), [](const std::pair<char, int>& a, const std::pair<char, int>& b) {
            return a.second > b.second || (a.second == b.second && a.first < b.first);
        });

        std::string generatedChecksum;
        for (int i = 0; i < std::min(5, (int)vec.size()); i++) {
            generatedChecksum.push_back(vec[i].first);
        }

        return generatedChecksum == checkLetters;
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
    int sectorIDSum = 0;

    while (getline(file, line)) {
        std::size_t lastDash = line.find_last_of('-');
        std::size_t bracketPos = line.find('[');
        if (lastDash != std::string::npos && bracketPos != std::string::npos && bracketPos > lastDash) {
            std::string roomName = line.substr(0, lastDash);
            std::string sectorIDStr = line.substr(lastDash + 1, bracketPos - lastDash - 1);
            std::string checkLetters = line.substr(bracketPos + 1, 5);

            int sectorID = std::stoi(sectorIDStr);

            Room currentRoom(roomName, sectorID, checkLetters);
            if (currentRoom.isValid) {
                sectorIDSum += sectorID;
                validCount++;
            }
        }
    }

    file.close();
    std::cout << "Sum of sector IDs of valid rooms: " << sectorIDSum << std::endl;
    return 0;
}
