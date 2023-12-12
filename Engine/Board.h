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
        Tetriminos* b = new T;
    public:
        Board();
        vector<vector<bool>> board;
        void createBoard();
        void print();
        void draw();
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
            cout << " ."[j == 0] << (toDraw[i][j] ? "#" : " ") << " ."[j == 9];
        cout << endl;
    }
}

bool Board::isCollied(vector<pair<int,int>> pos){
    for (int i = 0; i < pos.size(); i++)
        if (pos[i].first >= HEIGHT || pos[i].first < 0 || 
            pos[i].second >= WIDTH || pos[i].second < 0 ||
            board[pos[i].first][pos[i].second] != 0) {
                cout << "Cant go\n";
                return true;
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
            break;
        case 3:
            cout << "Case 3\n";
            if (!isCollied(b->GoRight(true))){
                b->GoRight();
            }
            break;
        case 5:
            cout << "Flip clock wise\n";
            if (!isCollied(b->ClockWiseRotate(true)))
                b->ClockWiseRotate();
            break;
    }
    
    cout << b->y << "+" << b->x << endl;
    
}


