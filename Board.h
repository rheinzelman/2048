//
// Created by Ray on 3/12/2023.
//

#ifndef INC_2048_BOARD_H
#define INC_2048_BOARD_H

#include <iostream>
#include <tuple>
#include <vector>

enum Direction {up, right, down, left};

class Board {
public:
    Board(int dimensions);
    ~Board();

    void initBoard();
    int generateTileValue();
    std::vector<int> generateTilePos();
    bool makeMove(Direction direction);
    bool checkCombine(int x, int y, Direction direction) const;
    int** getEmptySquares() const;
    std::vector<std::vector<int>> getPossibleCombos() const;
    void printBoard() const;

    //dev
    void setBoard();

    int getBoardSize();

private:
    int** board;
    int BOARD_SIZE;
    int boardSize;
    int score;
    int moveCount;
    int tileGenProbability; // number between 1-100 used to determine likelihood of spawning a 4
};


#endif //INC_2048_BOARD_H
