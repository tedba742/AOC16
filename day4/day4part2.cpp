#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

struct Room {
    std::string roomName;
    int sectorID;
    std::string checkLetters;

    Room(const std::string& name, int id, const std::string& checksum) :
        roomName(name), sectorID(id), checkLetters(checksum) {
    }

    std::string decryptRoomName() {
        std::string decryptedName;
        for (char c : roomName) {
            if (c == '-') {
                decryptedName += ' ';
            } else {
                char rotated = 'a' + (c - 'a' + sectorID) % 26;
                decryptedName += rotated;
            }
        }
        return decryptedName;
    }
};

bool isNorthPole(Room& room) {
    std::string decryptedName = room.decryptRoomName();
    if (decryptedName.find("northpole") != std::string::npos) {
        return true;
    }
    return false;
}

int main() {
    std::fstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }

    std::string line;

    while (getline(file, line)) {
        std::size_t lastDash = line.find_last_of('-');
        std::size_t bracketPos = line.find('[');
        if (lastDash != std::string::npos && bracketPos != std::string::npos && bracketPos > lastDash) {
            std::string roomName = line.substr(0, lastDash);
            std::string sectorIDStr = line.substr(lastDash + 1, bracketPos - lastDash - 1);
            std::string checkLetters = line.substr(bracketPos + 1, bracketPos - lastDash - 6);

            int sectorID = std::stoi(sectorIDStr);

            Room currentRoom(roomName, sectorID, checkLetters);
            if (isNorthPole(currentRoom)) {
                std::cout << "North Pole objects are stored in room sector ID: " << currentRoom.sectorID << std::endl;
                break;
            }
        }
    }

    file.close();
}
