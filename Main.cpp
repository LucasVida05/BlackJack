#include "Game.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

int main () {
#ifdef _WIN32
    // Ensure console uses UTF-8 so suit symbols render correctly.
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // Enable ANSI escape processing for colors
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD mode = 0;
        if (GetConsoleMode(hOut, &mode)) {
            SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        }
    }
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Game game;
    char playAgain;
    
    do {
        game.startRound();
        
        std::cout << "\nPlay again? (y/n): " << std::flush;
        std::cin >> playAgain;
        std::cin.ignore(10000, '\n');
        
    } while (playAgain == 'y' || playAgain == 'Y');
    
    std::cout << "Thanks for playing!" << std::endl;
    return 0;
}