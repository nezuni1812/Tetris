#pragma once

#ifndef _TETRIMINO_
#define _TETRIMINO_
#include <iostream>
#include <vector>
#include <chrono>

const int initialx = -100;
const int initialy = -100;
const int currentRotation = -100;

class Pixel {
public:
    bool filled;
    int color;
    Pixel(bool filled = false, int color = 0) : filled(filled), color(color) {}
};

using namespace std;
class Tetriminos {
private:
    const int HEIGHT = 20;
    const int WIDTH = 10;
    vector<vector<vector<pair<int, int>>>> wallKickCase;
    int color;
    char type;
    unsigned long long waitTime;
public:
    unsigned long long lastUpdate;
    Tetriminos(int x, int y, int color, char type);
    int currentRotation = 0;
    int x = -1, y = -1;
    vector<vector<vector<Pixel>>> states;
    bool cannotGoDown = false;
    
    void InitWallKick(int type);
    void SetColor();
    void SetWaitTime(int wait) {
        if (wait <= 1)
            this->waitTime = 1200;
        else if (wait <= 2)
            this->waitTime = 900;
        else if (wait <= 3)
            this->waitTime = 600;
        else
            this->waitTime = 290;
    }
    
    bool isCollided(vector<vector<Pixel>> board, int _x, int _y, int _currentState);
    bool isObstructedDown() {
        return cannotGoDown;
    }
    
    uint64_t timeSinceEpochMillisec();
    void LastUpdate();
    bool Continue(vector<vector<Pixel>> board);
    void Rotate(vector<vector<Pixel>> board, bool clockWise);
    bool GoDown(vector<vector<Pixel>> board);
    bool HardDrop(vector<vector<Pixel>> board);
    bool GoLeft(vector<vector<Pixel>> board);
    bool GoRight(vector<vector<Pixel>> board);
    
    vector<pair<int, int>> GetAllPoints(int _x, int _y, int _currentState);
    vector<pair<int, int>> GetGhostTetromino(vector<vector<Pixel>> board);
    int GetColor() {
        return color;
    }
    char GetType() {
        return type;
    }
};


class O: public Tetriminos {
public:
    O(int x = 4, int y = 0) : Tetriminos(x, y, 7, 'O') {
        InitWallKick(0);
        states.resize(4);
        
        states[0] = {
                    {1, 1},
                    {1, 1},
                    };
                    
        for (int i = 1; i < 4; i++)
            states[i] = states[0];
        SetColor();
    }
};

class I: public Tetriminos {
public:
    I(int x = 4, int y = 0) : Tetriminos(x, y, 1, 'I') {
        InitWallKick(1);
        states.resize(4);
        
        states[0] = {
                    {0, 0, 0, 0},
                    {1, 1, 1, 1},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0},
                    };
                    
        states[1] = {
                    {0, 0, 1, 0},
                    {0, 0, 1, 0},
                    {0, 0, 1, 0},
                    {0, 0, 1, 0},
                    };
        states[2] = {
                    {0, 0, 0, 0},
                    {0, 0, 0, 0},
                    {1, 1, 1, 1},
                    {0, 0, 0, 0},
                    };
        states[3] = {
                    {0, 0, 1, 0},
                    {0, 0, 1, 0},
                    {0, 0, 1, 0},
                    {0, 0, 1, 0},
                    };        
        SetColor();
    }
};

class J: public Tetriminos {
public:
    J(int x = 4, int y = 0) : Tetriminos(x, y, 2, 'J') {
        InitWallKick(0);
        states.resize(4);
        
        states[0] = {
                    {1, 0, 0},
                    {1, 1, 1},
                    {0, 0, 0},
                    };
                    
        states[1] = {
                    {0, 1, 1},
                    {0, 1, 0},
                    {0, 1, 0},
                    };
        states[2] = {
                    {0, 0, 0},
                    {1, 1, 1},
                    {0, 0, 1},
                    };
                    
        states[3] = {
                    {0, 1, 0},
                    {0, 1, 0},
                    {1, 1, 0},
                    };  
        SetColor();
    }
};

class L: public Tetriminos {
public:
    L(int x = 4, int y = 0) : Tetriminos(x, y, 3, 'L') {
        InitWallKick(0);
        states.resize(4);
        
        states[0] = {
                    {0, 0, 1},
                    {1, 1, 1},
                    {0, 0, 0},
                    };
                    
        states[1] = {
                    {0, 1, 0},
                    {0, 1, 0},
                    {0, 1, 1},
                    };
        states[2] = {
                    {0, 0, 0},
                    {1, 1, 1},
                    {1, 0, 0},
                    };
                    
        states[3] = {
                    {1, 1, 0},
                    {0, 1, 0},
                    {0, 1, 0},
                    };  
        SetColor();
    }
};


class S: public Tetriminos {
public:
    S(int x = 4, int y = 0) : Tetriminos(x, y, 4, 'S') {
        InitWallKick(0);
        states.resize(4);
        
        states[0] = {
                    {0, 1, 1},
                    {1, 1, 0},
                    {0, 0, 0},
                    };
                    
        states[1] = {
                    {0, 1, 0},
                    {0, 1, 1},
                    {0, 0, 1},
                    };
        states[2] = {
                    {0, 0, 0},
                    {0, 1, 1},
                    {1, 1, 0},
                    };
        states[3] = {
                    {1, 0, 0},
                    {1, 1, 0},
                    {0, 1, 0},
                    };    
        SetColor();
    }
};

class T: public Tetriminos {
public:
    T(int x = 4, int y = 0) : Tetriminos(x, y, 5, 'T') {
        InitWallKick(0);
        states.resize(4);
        
        states[0] = {
                    {0, 1, 0},
                    {1, 1, 1},
                    {0, 0, 0},
                    };
                    
        states[1] = {
                    {0, 1, 0},
                    {0, 1, 1},
                    {0, 1, 0},
                    };
        states[2] = {
                    {0, 0, 0},
                    {1, 1, 1},
                    {0, 1, 0},
                    };
        states[3] = {
                    {0, 1, 0},
                    {1, 1, 0},
                    {0, 1, 0},
                    };   
        SetColor();
    }
};


class Z: public Tetriminos {
public:
    Z(int x = 5, int y = 0) : Tetriminos(x, y, 6, 'Z') {
        InitWallKick(0);
        states.resize(4);
        
        states[0] = {
                    {1, 1, 0},
                    {0, 1, 1},
                    {0, 0, 0},
                    };
                    
        states[1] = {
                    {0, 0, 1},
                    {0, 1, 1},
                    {0, 1, 0},
                    };
        states[2] = {
                    {0, 0, 0},
                    {1, 1, 0},
                    {0, 1, 1},
                    };
        states[3] = {
                    {0, 1, 0},
                    {1, 1, 0},
                    {1, 0, 0},
                    };        
        SetColor();
    }
};

#endif