//
// Created by Ray on 3/12/2023.
//

#ifndef INC_2048_GAME_H
#define INC_2048_GAME_H

#include "Board.h"
#include<string>
#include<iostream>
#include<limits>

class Game {
public:
    Game(std::string playerName, int boardSize);

    void startGame();

    int getScore();
    void addScore(int additionalScore);
    int getMoveCount();
    void addMoveCount();
    bool isGameOver();
    bool pollMove();

private:
    std::string player;
    Board board;
    int score;
    int moveCount;

};


#endif //INC_2048_GAME_H
