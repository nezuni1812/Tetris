#pragma once

#include <bits/stdc++.h>
#include <conio.h>
#include "Block.cpp"

using namespace std;

class Board{
    private:
        int rows;
        int cols;
        int cellSize;
        int updateTime;
        const int HEIGHT = 20;
        const int WIDTH = 10;

        Tetriminos* b = new I;
        void moveRowDown(int row, int rows);

    public:
        Board();
        vector<vector<bool>> board;
        void createBoard();
        void print();
        void draw();
        void newTetriminos();
        void update();
        
        void clearRow(int row);
        bool isRowFull(int row);
        void clearFullRows();
        int score(int lineDeleted);
};