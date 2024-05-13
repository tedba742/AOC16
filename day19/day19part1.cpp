#include <iostream>
#include <list>

int main() {
    int input = 3005290;
    std::list<int> elves;

    for (int i = 1; i <= input; ++i) {
        elves.push_back(i);
    }

    auto currentElf = elves.begin();

    while (elves.size() > 1) {
        auto elfToRemove = next(currentElf);
        if (elfToRemove == elves.end()) {
            elfToRemove = elves.begin();
        }

        elfToRemove = elves.erase(elfToRemove);

        if (elfToRemove == elves.end()) {
            currentElf = elves.begin();
        } else {
            currentElf = elfToRemove;
        }

        if (currentElf == elves.end()) {
            currentElf = elves.begin();
        }
    }

    std::cout << "The elf with all the presents is: " << elves.front() << std::endl;

    return 0;
}
