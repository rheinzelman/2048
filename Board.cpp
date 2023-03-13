//
// Created by Ray on 3/12/2023.
//

#include "Board.h"


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
    vector<int> rSquare1 = generateTilePos();
    vector<int> rSquare2 = generateTilePos();

    while(rSquare1[0] == rSquare2[0] && rSquare1[1] == rSquare2[1]){
        rSquare1 = generateTilePos();
    }
    board[rSquare1[0]][rSquare1[1]] = generateTileValue();
    board[rSquare2[0]][rSquare2[1]] = generateTileValue();
}

int Board::generateTileValue() {
    int randNum = rand() % 100 + 1;
    if(randNum > tileGenProbability){
        return 2;
    } else{
        return 4;
    }
}

bool Board::makeMove(Direction direction) {
    int** emptySquaresPre = getEmptySquares();
    switch(direction){
        case Direction::up:
            break;
        case Direction::right:
            break;
        case Direction::down:
            break;
        case Direction::left:
            break;
    }
    int** emptySquares = getEmptySquares();
    return true;
}



vector<int> Board::generateTilePos() {
    vector<int> rPos;
    rPos.push_back(rand() % boardSize);
    rPos.push_back(rand() % boardSize);
    return rPos;
}

int** Board::getEmptySquares() const {
    int numEmptySquares = 0;
    for(int i=0; i < boardSize; i++){
        for(int j=0; j < boardSize; j++){
            if(board[i][j] == 0){
                numEmptySquares++;
            }
        }
    }
    int** emptySquares = new int*[numEmptySquares];
    for(int i=0; i < numEmptySquares; i++){
        emptySquares[i] = new int[2];
    }
    int emptySquaresIterator = 0;
    for(int i=0; i < boardSize; i++){
        for(int j=0; j < boardSize; j++){
            if(board[i][j] == 0){
                emptySquares[emptySquaresIterator][0] = i;
                emptySquares[emptySquaresIterator][1] = j;
                emptySquaresIterator++;
            }
        }
    }
    return emptySquares;
}

bool Board::checkCombine(int x, int y, Direction direction) const{
    switch(direction){
        case Direction::up:
            return (board[x][y] == board[x-1][y] && board[x][y] != 0);
        case Direction::right:
            return (board[x][y] == board[x][y+1] && board[x][y] != 0);
        case Direction::down:
            return (board[x][y] == board[x+1][y] && board[x][y] != 0);
        case Direction::left:
            return (board[x][y] == board[x][y-1] && board[x][y] != 0);
    }
}

vector<vector<int>> Board::getPossibleCombos() const {
    vector<vector<int>> possibleCombos;
    for(int i=0; i<boardSize; i++){
        for(int j=0; j<boardSize; j++){
            // left side
            if(j==0){
                // top left
                if(i==0){
                    // right
                    if(checkCombine(i,j, Direction::right)){
                        possibleCombos.push_back({i, j, i,j+1});
                    }
                    // down
                    if(checkCombine(i,j, Direction::down)){
                        possibleCombos.push_back({i, j, i+1,j});
                    }

                }
                // bottom left
                else if(i==boardSize-1){
                    // right
                    if(checkCombine(i,j,Direction::right)){
                        possibleCombos.push_back({i, j, i,j+1});
                    }
                    // up
                    if(checkCombine(i,j,Direction::up)){
                        possibleCombos.push_back({i, j, i-1,j});
                    }
                }
                // left side
                else{
                    // right
                    if(checkCombine(i,j,Direction::right)){
                        possibleCombos.push_back({i, j, i,j+1});
                    }
                    // up
                    if(checkCombine(i,j,Direction::up)){
                        possibleCombos.push_back({i, j, i-1,j});
                    }
                    // down
                    if(checkCombine(i,j,Direction::down)){
                        possibleCombos.push_back({i, j, i+1,j});
                    }
                }
            }
            // right side
            else if(j==boardSize-1){
                // top right
                if(i==0){
                    // left
                    if(checkCombine(i,j,Direction::left)){
                        possibleCombos.push_back({i, j, i,j-1});
                    }
                    // down
                    if(checkCombine(i,j,Direction::down)){
                        possibleCombos.push_back({i, j, i+1,j});
                    }
                }
                // bottom right
                else if(i==boardSize-1){
                    // up
                    if(checkCombine(i,j,Direction::up)){
                        possibleCombos.push_back({i, j, i-1,j});
                    }
                    // left
                    if(checkCombine(i,j,Direction::left)){
                        possibleCombos.push_back({i, j, i,j-1});
                    }
                }
                // right side
                else{
                    // up
                    if(checkCombine(i,j,Direction::up)){
                        possibleCombos.push_back({i, j, i-1,j});
                    }
                    // down
                    if(checkCombine(i,j,Direction::down)){
                        possibleCombos.push_back({i, j, i+1,j});
                    }
                    // left
                    if(checkCombine(i,j,Direction::left)){
                        possibleCombos.push_back({i, j, i,j-1});
                    }
                }
            }
            // middle
            else{
                // middle top
                if(i==0){
                    // down
                    if(checkCombine(i,j,Direction::down)){
                        possibleCombos.push_back({i, j, i+1,j});
                    }
                    // left
                    if(checkCombine(i,j,Direction::left)){
                        possibleCombos.push_back({i, j, i,j-1});
                    }
                    // right
                    if(checkCombine(i,j,Direction::right)){
                        possibleCombos.push_back({i, j, i,j+1});
                    }
                }
                // middle bottom
                else if(i==boardSize-1){
                    // up
                    if(checkCombine(i,j,Direction::up)){
                        possibleCombos.push_back({i, j, i-1,j});
                    }
                    // left
                    if(checkCombine(i,j,Direction::left)){
                        possibleCombos.push_back({i, j, i,j-1});
                    }
                    // right
                    if(checkCombine(i,j,Direction::right)){
                        possibleCombos.push_back({i, j, i,j+1});
                    }
                } else{
                    // up
                    if(checkCombine(i,j,Direction::up)){
                        possibleCombos.push_back({i, j, i-1,j});
                    }
                    // left
                    if(checkCombine(i,j,Direction::left)){
                        possibleCombos.push_back({i, j, i,j-1});
                    }
                    // right
                    if(checkCombine(i,j,Direction::right)){
                        possibleCombos.push_back({i, j, i,j+1});
                    }
                    // down
                    if(checkCombine(i,j,Direction::down)){
                        possibleCombos.push_back({i, j, i+1, j});
                    }
                }
            }
        }
    }
    return possibleCombos;
}

void Board::printBoard() const {
    for(int i=0; i < boardSize; i++){
        for(int j=0; j < boardSize; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int Board::getBoardSize() {
    return boardSize;
}

void Board::setBoard() {
//    for(int i=0; i<boardSize; i++){
//        for(int j=0; j<boardSize; j++){
//            board[i][j] = newBoard[i][j];
//        }
//    }

    board[0][0] = 2;
    board[0][1] = 2;
    board[1][1] = 2;
    board[1][2] = 2;
}
