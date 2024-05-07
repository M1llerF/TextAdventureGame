#include <iostream>
#include "GameManager.h"

int main() {
    GameManager game; // GameManager object init
    game.initGame();
    game.startGame(std::cin);
    return 0;
}
