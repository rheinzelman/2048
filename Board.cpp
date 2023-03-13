//
// Created by Ray on 3/12/2023.
//

#include "Board.h"
#include <iostream>
#include <cstring>

using namespace std;

Board::Board(int dimensions){
    this->boardSize = dimensions;
    moveCount = 0;
    score = 0;

    board = new int*[dimensions];
    for(int i=0; i < dimensions; i++){
        board[i] = new int[dimensions];
        for(int j=0; j < dimensions; j++){
            board[i][j] = 0;
        }
    }

}

Board::~Board(){
    for(int i=0; i < boardSize; i++){
        delete[] board[i];
    }
    delete[] board;
}

void Board::printBoard() const {
    for(int i=0; i < boardSize; i++){
        for(int j=0; j < boardSize; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int Board::getScore(){
   return score;
}

void Board::addScore(int additionalScore) {
    score += additionalScore;
}

int Board::getMoveCount() {
    return moveCount;
}

void Board::addMoveCount() {
    moveCount++;
}
