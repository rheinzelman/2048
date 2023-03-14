//
// Created by Ray on 3/12/2023.
//

#include "Game.h"

using namespace std;

Game::Game(string playerName, int boardSize) : board(boardSize){
    player = playerName;
    board.initBoard();
}

void Game::startGame() {
    while(!isGameOver()){

    }
}

int Game::getScore() {
    return score;
}

void Game::addScore(int additionalScore) {
    score += additionalScore;
}

int Game::getMoveCount() {
    return moveCount;
}

void Game::addMoveCount() {
    moveCount++;
}

bool Game::isGameOver() {
    vector<vector<int>> possibleCombos = board.getPossibleCombos();
    if(possibleCombos.empty() && board.getEmptySquares() == 0){
        return true;
    } else{
        return false;
    }
}
