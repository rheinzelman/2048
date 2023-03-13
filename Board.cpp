//
// Created by Ray on 3/12/2023.
//

#include "Board.h"
#include <iostream>
#include <tuple>

using namespace std;

Board::Board(int dimensions){
    this->boardSize = dimensions;
    tileGenProbability = 10;
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

void Board::initBoard() {
    int* rSquare1 = generateTilePos();
    int* rSquare2 = generateTilePos();

    while(rSquare1[0] == rSquare2[0] && rSquare1[1] == rSquare2[1]){
        rSquare1 = generateTilePos();
    }
    board[rSquare1[0]][rSquare1[1]] = generateTileValue();
    board[rSquare2[0]][rSquare2[1]] = generateTileValue();

    delete[] rSquare1;
    delete[] rSquare2;
}

int Board::generateTileValue() {
    int randNum = rand() % 100 + 1;
    if(randNum > tileGenProbability){
        return 2;
    } else{
        return 4;
    }
}

int* Board::generateTilePos() {
    int randNum1 = rand() % boardSize;
    int randNum2 = rand() % boardSize;
    int* rPos = new int[2]{randNum1, randNum2};
    return rPos;
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
