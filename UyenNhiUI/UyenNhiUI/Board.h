#pragma once
#include <conio.h>
#include <string>
#include "Block.h"

using namespace std;

class Board{
    private:
        int rows;
        int cols;
        int cellSize;
        int updateTime;
        
        Tetriminos* b = new S;
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
        int clearFullRows();
        int updateScore(int lineDeleted);
        bool isOver();

        int score = 0;
};