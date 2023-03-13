#include <iostream>
#include <ctime>
#include "Board.h"
#include "Game.h"

int main() {

    // set time seed
    srand(time(NULL));

    Board board(4);
    board.initBoard();
    board.printBoard();
    board.setBoard();
    board.printBoard();
    std::vector<std::vector<int>> test = board.getPossibleCombos();
    for(int i=0;i<test.size();i++){
        std::cout << test[i][0] << ", " << test[i][1] << " : " << test[i][2] << ", " << test[i][3] << "\n";
    }

    return 0;
}
