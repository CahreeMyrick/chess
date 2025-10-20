#include "chess/game.hpp"
#include "chess/strategy.hpp"
#include <iostream>
#include <string>

using namespace chess;

int main() {
    Game game;

    // Reusable AIs
    MinimaxStrategy aiWhite;
    MinimaxStrategy aiBlack;
    aiWhite.max_depth = 3;
    aiBlack.max_depth = 3;

    std::cout << "Choose game mode:\n"
              << "  1) Human (White) vs AI (Black)\n"
              << "  2) AI (White) vs Human (Black)\n"
              << "  3) AI vs AI\n"
              << "  4) Human vs Human (Player vs Player)\n"
              << "Enter 1-4: ";

    int mode = 0;
    std::string line;
    if (!std::getline(std::cin, line)) return 0;
    try { mode = std::stoi(line); } catch (...) {mode = 0;}

    Strategy* white = nullptr;
    Strategy* black = nullptr;

    switch (mode) {
        case 1: // Human (White) vs AI (Black)
            white = nullptr;
            black = &aiBlack;
            break;
        case 2: // AI (White) vs Human (Black)
            white = &aiWhite;
            black = nullptr;
            break;
        case 3: // AI vs AI
            white = &aiWhite;
            black = &aiBlack;
            break;
        case 4: // Human vs Human (PvP)
            white = nullptr;
            black = nullptr;
            break;
        default:
            std::cout << "Invalid choice. Defaulting to Human (White) vs AI (Black).\n";
            white = nullptr;
            black = &aiBlack;
            break;
    }

    game.loop_with_strategies(white, black);
    return 0;
}
