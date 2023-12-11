#include "board.h"
Board::Board(){
    rows = 20;
    cols = 10;
    cellSize = 30;
    createBoard();

}

void Board::createBoard(){
    for(int row = 0; row < rows; row++){
        for(int col = 0; col < cols; col++){
            board[row][col] = 0;
        }
    }
}

void Board::print(){
    for(int row = 0; row < rows; row++){
        for(int col = 0; col < cols; col++){
            cout << board[row][col];
        }
        cout << endl;
    }
}

void Board::draw(){
    vector<vector<bool>> shape = b->states[b->currentState];
    vector<vector<bool>> toDraw(20, vector<bool>(10, 0));

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++)
            if(board[i][j] == 1)
                toDraw[i][j] = 1;
    }
    
    for(int i = 0; i < shape.size(); i++){
        for(int j = 0; j < shape[0].size(); j++)
            if(shape[i][j] == 1){
                toDraw[i + b->y][j + b->x] = 1;
            }
    }

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++)
            cout << toDraw[i][j];
        cout << endl;
    }
}

bool Board::isCollied(vector<pair<int,int>>){

}

void Board::update(){
    int n;
    cin >> n;
    switch(n){
        case(1):
            b->x--;
            b->y--;
            if(b->x < 0)
                b->x = 0;
            if(b->y < 0)
                b->y = 0;
            break;
        case(3):
            b->x++;
            b->y++;
            if(b->x > 10)
                b->x = 10;
            if(b->y < 0)
                b->y = 0;
            break;
        case(5):
            b->y++;
            if(b->y > 20)
                b->y = 20;
            break;
        case(2):
            b->y--;
            if(b->y < 0)
                b->y = 0;
            break;
    }
    
}