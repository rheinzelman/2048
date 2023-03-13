//
// Created by Ray on 3/12/2023.
//

#ifndef INC_2048_BOARD_H
#define INC_2048_BOARD_H

enum Direction {up, right, down, left};

class Board {
public:
    Board(int dimensions);
    ~Board();

    void initBoard();
    int generateTileValue();
    int* generateTilePos();
    bool makeMove(Direction direction);
    bool isGameOver() const;
    void printBoard() const;

    int getScore();
    void addScore(int additionalScore);

    int getMoveCount();
    void addMoveCount();

private:
    int BOARD_SIZE;
    int** board;
    int boardSize;
    int score;
    int moveCount;
    int tileGenProbability; // number between 1-100 used to determine likelihood of spawning a 4
};


#endif //INC_2048_BOARD_H
