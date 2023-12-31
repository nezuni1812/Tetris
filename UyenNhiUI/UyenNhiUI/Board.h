#pragma once
#include <conio.h>
#include <string>
#include <chrono>
#include "Block.h"

using namespace std;

class Board{
    private:
        int rows;
        int cols;
        int cellSize;
        int updateTime;
        bool overState = false;
        int currentPoint;
        int score = 0;
        bool hardMode;
        uint64_t startTime;
        
        Tetriminos* b;
        Tetriminos* nextTetromino;
        void moveRowDown(int row, int rows);
        vector<vector<Pixel>> board;

    public:
        Board(bool hardMode = false);
        ~Board();
        uint64_t timeSinceEpochMillisec();
        vector<vector<Pixel>> draw(bool drawOut);
        vector<vector<Pixel>> drawGhostPiece();
        void newTetriminos();
        void updateBlockWaitTime();
        void changeExistingStack();
        void update(string move);
        
        int GetPoints();
        uint64_t GetTimePlayed();
        char GetNextTetrominoType();

        void clearRow(int row);
        bool isRowFull(int row);
        int clearFullRows();
        int updateScore(int lineDeleted);
        bool isOver();

};