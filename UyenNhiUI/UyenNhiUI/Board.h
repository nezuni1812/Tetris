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
        
        Tetriminos* b = new S;
        Tetriminos* nextTetromino;
        void moveRowDown(int row, int rows);

    public:
        Board(bool hardMode = false);
        vector<vector<Pixel>> board;
        uint64_t timeSinceEpochMillisec() {
            using namespace std::chrono;
            return duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch()).count();
        }
        void createBoard();
        void print();
        vector<vector<Pixel>> draw(bool drawOut);
        vector<vector<Pixel>> drawGhostPiece();
        void newTetriminos();
        void updateBlockWaitTime();
        void changeExistingStack();
        void update(string move);
        
        Tetriminos* GetCurrentTetromino() {
            return b;
        }
        Tetriminos* GetNextTetromino() {
            return nextTetromino;
        }
        int GetPoints() {
            return score;
        }
        uint64_t GetTimePlayed() {
            return timeSinceEpochMillisec() - startTime;
        }

        void clearRow(int row);
        bool isRowFull(int row);
        int clearFullRows();
        int updateScore(int lineDeleted);
        bool isOver();

};