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
        bool overState = false;
        
        Tetriminos* b = new S;
        void moveRowDown(int row, int rows);

    public:
        Board();
        vector<vector<Pixel>> board;
        void createBoard();
        void print();
        vector<vector<Pixel>> draw(bool drawOut);
        void newTetriminos();
        void update(string move);
        /*vector<vector<Pixel>> GetBoard() {
            vector<vector<Pixel>> toDraw = 

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