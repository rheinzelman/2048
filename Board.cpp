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
// for each tile
// move in the direction until it hits the edge or another tile
int Board::makeMove(Direction direction) {
    // Traverse the board in the given direction
    switch (direction) {
        case Direction::up:
            for (int j = 0; j < boardSize; j++) { // Column-wise traversal
                int i = 0;
                while (i < boardSize - 1) { // Traverse each row
                    if (board[i][j] == 0) { // If current element is 0
                        int k = i + 1;
                        while (k < boardSize && board[k][j] == 0) // Find the next non-zero element
                            k++;
                        if (k < boardSize) { // Swap the current and next non-zero elements
                            board[i][j] = board[k][j];
                            board[k][j] = 0;
                            i--; // Move back to check if there are any more 0's before the swapped element
                        }
                    }
                    i++;
                }
            }
            break;
        case Direction::down:
            for (int j = 0; j < boardSize; j++) { // Column-wise traversal
                int i = boardSize - 1;
                while (i > 0) { // Traverse each row
                    if (board[i][j] == 0) { // If current element is 0
                        int k = i - 1;
                        while (k >= 0 && board[k][j] == 0) // Find the next non-zero element
                            k--;
                        if (k >= 0) { // Swap the current and next non-zero elements
                            board[i][j] = board[k][j];
                            board[k][j] = 0;
                            i++; // Move back to check if there are any more 0's before the swapped element
                        }
                    }
                    i--;
                }
            }
            break;
        case Direction::left:
            for (int i = 0; i < boardSize; i++) { // Row-wise traversal
                int j = 0;
                while (j < boardSize - 1) { // Traverse each column
                    if (board[i][j] == 0) { // If current element is 0
                        int k = j + 1;
                        while (k < boardSize && board[i][k] == 0) // Find the next non-zero element
                            k++;
                        if (k < boardSize) { // Swap the current and next non-zero elements
                            board[i][j] = board[i][k];
                            board[i][k] = 0;
                            j--; // Move back to check if there are any more 0's before the swapped element
                        }
                    }
                    j++;
                }
            }
            break;
        case Direction::right:
            for (int i = 0; i < boardSize; i++) { // Row-wise traversal
                int j = boardSize - 1;
                while (j > 0) { // Traverse each column
                    if (board[i][j] == 0) { // If current element is 0
                        int k = j - 1;
                        while (k >= 0 && board[i][k] == 0) //
                            k--;
                        if (k >= 0) { // Swap the current and next non-zero elements
                            board[i][j] = board[i][k];
                            board[i][k] = 0;
                            j++; // Move back to check if there are any more 0's before the swapped element
                        }
                    }
                    j--;
                }
            }
            break;
        default:
            cout << "Invalid direction!" << endl;
            break;
    }

    return 0;
}

// go to {direction} most tile
// if the one in the opposite direction is the same tile, put *2 on the initial comparison tile, put zero on the other tile
// shift all other tiles in the same line in the direction
// repeat until the end is reached

int Board::combineTiles(Direction direction) {
    switch(direction){
        case Direction::up:
            for(int i=0; i<boardSize; i++){
                for(int j=0; j<boardSize-1;j++){
                    if(board[j][i] == board[j+1][i]){
                        board[j][i] = board[j][i]*2;
                        for(int k=j+1; k<boardSize; k++){
                            if(k<boardSize-1){
                                board[k][i] = board[k+1][i];
                            } else {
                                board[k][i] = 0;
                            }
                        }
                    }
                }
            }
            break;
        case Direction::down:
            // for each column
            for(int i=0; i<boardSize; i++){
                // for each row in a given column
                for(int j=boardSize-1; j>0;j--){
                    // if the tile is equal to the tile above it
                    if(board[j][i] == board[j-1][i]){
                        // make the first tile *2
                        board[j][i] = board[j][i]*2;
                        // for each tile above the tile just multiplied
                        for(int k=j-1; k>=0; k--){
                            if(k>0){
                                board[k][i] = board[k-1][i];
                            } else {
                                board[k][i] = 0;
                            }
                        }
                    }
                }
            }
            break;
        case Direction::left:

            break;
        case Direction::right:

            break;
    }
}

//for(int i=0; i<possibleCombos.size();i++){
//if(possibleCombos[i][0] - possibleCombos[i][2] == 1 && (possibleCombos[i][0] != previouslyCombined[0]) && (possibleCombos[i][1] != previouslyCombined[1])){
//board[possibleCombos[i][2]][possibleCombos[i][3]] = board[possibleCombos[i][2]][possibleCombos[i][3]]*2;
//previouslyCombined = {possibleCombos[i][0], possibleCombos[i][1]};
//for(int j=possibleCombos[i][0]; j<=boardSize-1; j++){
//board[j][possibleCombos[i][1]] = board[j+1][possibleCombos[i][1]];
//if(j == boardSize-1){
//board[j][possibleCombos[i][1]] = 0;
//}
//}
//}
//}

vector<int> Board::generateTilePos() {
    vector<int> rPos;
    rPos.push_back(rand() % boardSize);
    rPos.push_back(rand() % boardSize);
    return rPos;
}

bool Board::generateTile(){
    if(getNumEmptySquares() != 0){
        vector<int> pos = generateTilePos();
        int value = generateTileValue();
        while(board[pos[0]][pos[1]] != 0){
            pos = generateTilePos();
        }
        board[pos[0]][pos[1]] = value;
    }
}

int Board::getNumEmptySquares() const {
    int numEmptySquares = 0;
    for(int i=0; i < boardSize; i++){
        for(int j=0; j < boardSize; j++){
            if(board[i][j] == 0){
                numEmptySquares++;
            }
        }
    }
    return numEmptySquares;
}

int** Board::getEmptySquares() const {
    int numEmptySquares = getNumEmptySquares();
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
//    if(possibleCombos.size() >= 1){
//        for(int i=0; i<possibleCombos.size();i++){
//            for(int j=i+1;j<possibleCombos.size();j++){
//                if((possibleCombos[i][0] == possibleCombos[j][2]) && (possibleCombos[i][1] == possibleCombos[j][3])){
//                    possibleCombos.erase(possibleCombos.begin()+j);
//                }
//            }
//        }
//    }


    return possibleCombos;
}

void Board::printBoard() const {
    cout << "========" << "\n";
    for(int i=0; i < boardSize; i++){
        for(int j=0; j < boardSize; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int Board::getNumPossibleCombos() const {
    vector<vector<int>> possibleCombos = getPossibleCombos();
    return possibleCombos.size()/2;
}

int Board::getBoardSize() {
    return boardSize;
}

void Board::setBoard() {
    int newBoard[4][4] = {
    {2, 0, 0, 4},
    {2, 2, 4, 4},
    {2, 2, 2, 2},
    {2, 0, 2, 2}
    };
    for(int i=0; i<boardSize; i++){
        for(int j=0; j<boardSize; j++){
            board[i][j] = newBoard[i][j];
        }
    }
}
