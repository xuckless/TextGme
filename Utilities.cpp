#include "Utilities.h"
#include <iostream>

void displayLevelTransition(int level) { //this is the display for the level when it starts
    std::cout << "\n===================================" << std::endl;
    std::cout << "           LEVEL " << level << "            " << std::endl;
    std::cout << "===================================" << std::endl;
    std::cout << "Get ready for your next challenge!" << std::endl;
}

void clearScreen() {
    std::cout << "\033[2J\033[1;1H"; // ANSI escape code to clear screen and move cursor to top-left
}


