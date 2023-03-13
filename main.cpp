#include <iostream>
#include <ctime>
#include "Board.h"

int main() {

    srand(time(NULL));

    Board mainBoard(4);
    mainBoard.printBoard();
    mainBoard.initBoard();
    std::cout << std::endl;
    mainBoard.printBoard();

    return 0;
}
