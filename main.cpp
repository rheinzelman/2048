#include <iostream>
#include <ctime>
#include "Board.h"
#include "Game.h"

int main() {

    // set time seed
    srand(time(NULL));

    Game game("Ray", 3);
    game.startGame();

    return 0;
}
