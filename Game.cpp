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
        cout << board.getNumEmptySquares() << ", " << board.getNumPossibleCombos() << endl;
        pollMove();
        board.generateTile();
    }
}

bool Game::pollMove(){
    string move;
    while(cout << "Enter a move (up, down, left, right): " && !(cin >> move) || (move != "up" && move != "down" && move != "left" && move != "right" && move != "c")){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input, try again\n";
    }
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
        for(int i=0; i<possibleCombos.size();i++){
            cout << possibleCombos[i][0] << ", " << possibleCombos[i][1] << " : " << possibleCombos[i][2] << ", " << possibleCombos[i][3] << endl;
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
    if(board.getNumEmptySquares() == 0 && board.getNumPossibleCombos() == 0){
        return true;
    } else{
        return false;
    }
}
