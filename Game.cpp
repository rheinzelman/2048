//
// Created by Ray on 3/12/2023.
//

#include "Game.h"

using namespace std;

Game::Game(string playerName, int boardSize) : board(boardSize){
    player = playerName;
    board.initBoard();
    score = 0;
}

void Game::startGame() {
    while(!isGameOver()){
        vector<vector<int>> possibleCombos = board.getPossibleCombos();
        cout << "Score: " << getScore() << endl;
        board.printBoard();
        Direction moveDirection = pollMove();
        int additionalScore = board.combineTiles(moveDirection);
        addScore(additionalScore);
        board.generateTile();
    }
}

Direction Game::pollMove(){
    string move;
    while(cout << "Enter a move (up, down, left, right): " && !(cin >> move) || (move != "up" && move != "down" && move != "left" && move != "right" && move != "c")){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input, try again\n";
    }
    Direction moveDirection;
    if(move == "up"){
        board.makeMove(Direction::up);
        return(Direction::up);
    } else if(move == "right"){
        board.makeMove(Direction::right);
        return(Direction::right);

    } else if(move == "down"){
        board.makeMove(Direction::down);
        return(Direction::down);

    } else if(move == "left"){
        board.makeMove(Direction::left);
        return(Direction::left);

    } else if(move=="c"){
        vector<vector<int>> possibleCombos = board.getPossibleCombos();
        for(int i=0; i<possibleCombos.size();i++){
            cout << possibleCombos[i][0] << ", " << possibleCombos[i][1] << " : " << possibleCombos[i][2] << ", " << possibleCombos[i][3] << endl;
        }
        return(Direction::up);
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
    if(board.getNumEmptySquares() == 0){
        if(board.getNumPossibleCombos())
        return true;
    } else{
        return false;
    }
}
