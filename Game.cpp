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
        board.printBoard();
        pollMove();
        board.generateTile();
    }
}

void Game::pollMove(){
    cout << "Enter a move (up, down, left, right): ";
    string move;
    cin >> move;
    if(move == "up"){
        board.makeMove(Direction::up);
    } else if(move == "right"){
        board.makeMove(Direction::right);
    } else if(move == "down"){
        board.makeMove(Direction::down);
    } else if(move == "left"){
        board.makeMove(Direction::left);
    } else if(move=="c"){
        vector<vector<int>> possibleCombos = board.getPossibleCombos();
        for(int i=0; i<board.getBoardSize();i++){
            cout << possibleCombos[i][0] << ", " << possibleCombos[i][1] << " : " << possibleCombos[i][2] << ", " << possibleCombos[i][3];
        }
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
