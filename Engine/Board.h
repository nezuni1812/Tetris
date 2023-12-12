#pragma once

#include <bits/stdc++.h>
#include "Block.h"

using namespace std;

class Board{
    private:
        int rows;
        int cols;
        int cellSize;
        const int HEIGHT = 20;
        const int WIDTH = 10;
        Tetriminos* b = new Z;
    public:
        Board();
        vector<vector<bool>> board;
        void createBoard();
        void print();
        void draw();
        void newTetriminos();
        bool isCollied(vector<pair<int,int>>);
        void update();
};

Board::Board(){
    rows = 20;
    cols = 10;
    cellSize = 30;
    
    board = vector<vector<bool>>(20, (vector<bool>(10, 0)));
    // createBoard();

}

void Board::createBoard(){
    // for(int row = 0; row < rows; row++){
    //     for(int col = 0; col < cols; col++){
    //         board[row][col] = 0;
    //     }
    // }
}

void Board::print(){
    // for(int row = 0; row < rows; row++){
    //     for(int col = 0; col < cols; col++){
    //         cout << board[row][col];
    //     }
    //     cout << endl;
    // }
}

void Board::draw(){
    vector<vector<bool>> toDraw(20, vector<bool>(10, 0));

    // Transfer all points in board to toDraw matrix 
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++)
            if(board[i][j] == 1)
                toDraw[i][j] = 1;
    }
    
    // Transfer all points in block b to toDraw matrix
    vector<pair<int,int>> pos = b->GetAllPoints();
    for (int i = 0; i < pos.size(); i++) {
        // cout << pos[i].first << " & " << pos[i].second << endl;
        toDraw[pos[i].first][pos[i].second] = true;
    }

    // Paint the toDraw matrix out
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++)
            cout << (j == 0 ? "." : "") << (toDraw[i][j] ? "#" : " ") << (j == 9 ? "." : "");
        cout << endl;
    }
}

void Board::newTetriminos() {
    if (b)
        delete b;
        
    int val = rand()% 6;
    
    switch (val)
    {
    case 0:
        b = new O;
        break;
        
    case 1:
        b = new I;
        break;
        
    case 2:
        b = new L;
        break;
        
    case 3:
        b = new S;
        break;
        
    case 4:
        b = new T;
        break;
        
    case 5:
        b = new Z;
        break;
    
    default:
        break;
    }
    
}

bool Board::isCollied(vector<pair<int,int>> pos){
    for (int i = 0; i < pos.size(); i++) {
        cout << pos[i].first << ", " << pos[i].second << endl;
        if (pos[i].first >= HEIGHT || pos[i].first < 0 || 
            pos[i].second >= WIDTH || pos[i].second < 0 ||
            board[pos[i].first][pos[i].second] != 0) {
                cout << "Cant go\n";
                return true;
            }
    }
            
    return false;
    
}

void Board::update(){
    int n;
    cout << "(1) for Left, (3) for Right, (5) to Transform: ";
    cin >> n;
    
    bool result;
    switch (n) {
        case 1:
            cout << "Case 1\n";
            if (!isCollied(b->GoLeft(true))){
                b->GoLeft();
            }
            else {
                if (!isCollied(b->GoDown(true)))
                    b->GoDown();
                else b->cannotGoDown = true;
            }
            break;
            
        case 3:
            cout << "Case 3\n";
            if (!isCollied(b->GoRight(true))){
                b->GoRight();
            }
            else {
                cout << "About to return value\n";
                bool res = isCollied(b->GoDown(true));
                cout << "Check if go down " << res << endl;
                if (!res) {
                    b->GoDown();
                }
                else {
                    cout << "Set cannot go down\n";
                    b->cannotGoDown = true;
                }
                cout << "Out of case 3\n";
            }
            break;
            
        case 5:
            cout << "Flip clock wise\n";
            if (!isCollied(b->ClockWiseRotate(true)))
                b->ClockWiseRotate();
            else {
                if (!isCollied(b->GoDown(true)))
                    b->GoDown();
                else b->cannotGoDown = true;
            }
            break;
            
        default:
            if (!isCollied(b->GoDown(true)))
                b->GoDown();
            else b->cannotGoDown = true;
    }
    
    // If the Tetriminos cannot go down anymore -> Merge it with the board
    if (b->cannotGoDown) {
        cout << "Creating new block\n";
        vector<pair<int,int>> pos = b->GetAllPoints();
        for (int i = 0; i < pos.size(); i++)
            board[pos[i].first][pos[i].second] = true;
        newTetriminos();
    }
    
    cout << b->y << "+" << b->x << endl;
    
}


