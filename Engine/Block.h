#include <bits/stdc++.h>

using namespace std;
class Tetriminos {
private:
    const int HEIGHT = 20;
    const int WIDTH = 10;
public:
    Tetriminos(int x, int y) : x(x), y(y) {};
    int currentState = 0;
    int x = -1, y = -1;
    vector<vector<vector<bool>>> states;
    
    virtual vector<pair<int,int>> ClockWiseRotate() = 0; 
    virtual vector<pair<int,int>> AntiClockWiseRotate() = 0;
    virtual vector<pair<int,int>> GoLeft(bool isTest = false) = 0; 
    virtual vector<pair<int,int>> GoRight(bool isTest = false) = 0; 
    
    vector<pair<int,int>> GetAllPoints(int x = -100, int y = -100) {
        if (x == -100) {
            x = this->x;
            y = this->y;
        }
        
        vector<pair<int,int>> points;
        for (int i = 0; i < states[currentState].size(); i++)
        for (int j = 0; j < states[currentState][0].size(); j++)
            if (states[currentState][i][j])
                points.push_back(make_pair(y + i, x + j));
                
        return points;
    }
};

class O: public Tetriminos {
public:
    O(int x = 4, int y = 0) : Tetriminos(x, y) {
        states.resize(4);
        
        states[0] = {
                    {1, 1},
                    {1, 1},
                    };
                    
        for (int i = 1; i < 4; i++)
            states[i] = states[0];
    }
    
    vector<pair<int,int>> ClockWiseRotate() {};
    vector<pair<int,int>> AntiClockWiseRotate() {};
    vector<pair<int,int>> GoLeft(bool isTest = false) {
        cout << "Went left\n";
        int _x = x - 1, _y = y + 1;
        if (isTest)
            return GetAllPoints(_x, _y);
        else
            cout << "Go left\n";
            x = _x; y = _y;
            return GetAllPoints();
    }; 
    vector<pair<int,int>> GoRight(bool isTest = false) {
        int _x = x + 1, _y = y + 1;
        if (isTest)
            return GetAllPoints(_x, _y);
        else
            cout << "Go right\n";
            x = _x; y = _y;
            return GetAllPoints();
    }; 
};

class I: public Tetriminos {
public:
    I(int x = 4, int y = 0) : Tetriminos(x, y) {
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
        states[0] = {
                    {0, 0, 0, 0},
                    {0, 0, 0, 0},
                    {1, 1, 1, 1},
                    {0, 0, 0, 0},
                    };
        states[0] = {
                    {0, 1, 0, 0},
                    {0, 1, 0, 0},
                    {0, 1, 0, 0},
                    {0, 1, 0, 0},
                    };        
    }
    
    vector<pair<int,int>> ClockWiseRotate() = 0; 
    vector<pair<int,int>> AntiClockWiseRotate() = 0;
};

class L: public Tetriminos {
public:
    L(int x = 4, int y = 0) : Tetriminos(x, y) {
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
        states[0] = {
                    {0, 0, 0},
                    {1, 1, 1},
                    {1, 0, 0},
                    };
                    
        states[0] = {
                    {1, 1, 0},
                    {0, 1, 0},
                    {0, 1, 0},
                    };        
    }
    
    
};


class S: public Tetriminos {
public:
    S(int x = 4, int y = 0) : Tetriminos(x, y) {
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
        states[0] = {
                    {0, 0, 0},
                    {0, 1, 1},
                    {1, 1, 0},
                    };
        states[0] = {
                    {1, 0, 0},
                    {1, 1, 0},
                    {0, 1, 0},
                    };        
    }
    
};

class T: public Tetriminos {
public:
    T(int x = 4, int y = 0) : Tetriminos(x, y) {
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
        states[0] = {
                    {0, 0, 0},
                    {1, 1, 1},
                    {0, 1, 0},
                    };
        states[0] = {
                    {0, 1, 0},
                    {1, 1, 0},
                    {0, 1, 0},
                    };        
    }
    
};


class Z: public Tetriminos {
public:
    Z(int x = 5, int y = 0) : Tetriminos(x, y) {
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
        states[0] = {
                    {0, 0, 0},
                    {1, 1, 0},
                    {0, 1, 1},
                    };
        states[0] = {
                    {0, 1, 0},
                    {1, 1, 0},
                    {1, 0, 0},
                    };        
    }
    
};
