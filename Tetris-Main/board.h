#include "bits/stdc++.h"
#include "block.h"
#pragma once

using namespace std;

class Board{
    private:
        int rows;
        int cols;
        int cellSize;
        Tetriminos* b = new O;
    public:
        Board();
        int board[20][10];
        void createBoard();
        void print();
        void draw();
        bool isCollied(vector<pair<int,int>>);
        void update();
};


