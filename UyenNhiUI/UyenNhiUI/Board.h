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
        vector<vector<bool>> draw(bool drawOut);
        void newTetriminos();
        void update(string move);
        /*vector<vector<bool>> GetBoard() {
            vector<vector<bool>> toDraw = 

            vector<pair<int, int>> pos = b->GetAllPoints(initialx, initialy, currentRotation);
            for (int i = 0; i < pos.size(); i++) {
                toDraw[pos[i].first][pos[i].second] = true;
            }
            return board;
        }*/
        
        void clearRow(int row);
        bool isRowFull(int row);
        int clearFullRows();
        int updateScore(int lineDeleted);
        bool isOver();

        int score = 0;
};