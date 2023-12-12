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
    bool cannotGoDown = false;
    
    virtual vector<pair<int,int>> ClockWiseRotate(bool isTest = false) = 0; 
    virtual vector<pair<int,int>> AntiClockWiseRotate(bool isTest = false) = 0;
    virtual vector<pair<int,int>> GoDown(bool isTest = false) = 0;
    vector<pair<int,int>> GoLeft(bool isTest = false) {
        // When isTest is true -> does not update x and y values to test if there is no collision
        cout << "Went left\n";
        int _x = x - 1, _y = y + 1;
        if (isTest)
            return GetAllPoints(_x, _y, currentState);
        else
            cout << "Go left\n";
            x = _x; y = _y;
            return GetAllPoints();
    }; 
    vector<pair<int,int>> GoRight(bool isTest = false) {
        // When isTest is true -> does not update x and y values to test if there is no collision
        int _x = x + 1, _y = y + 1;
        if (isTest)
            return GetAllPoints(_x, _y, currentState);
            
        cout << "Go right\n";
        x = _x; y = _y;
        return GetAllPoints();
    };  
    
    vector<pair<int,int>> GetAllPoints(int _x = -100, int _y = -100, int _currentState = -100) {
        if (_x == -100) {
            _x = this->x;
            _y = this->y;
            _currentState = this->currentState;
        }
        
        vector<pair<int,int>> points;
        for (int i = 0; i < states[_currentState].size(); i++)
        for (int j = 0; j < states[_currentState][0].size(); j++)
            if (states[_currentState][i][j])
                points.push_back(make_pair(_y + i, _x + j));
                
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
    
    vector<pair<int,int>> ClockWiseRotate(bool isTest = false) {};
    vector<pair<int,int>> AntiClockWiseRotate(bool isTest = false) {};
    vector<pair<int,int>> GoDown(bool isTest = false) {
        // When isTest is true -> does not update x and y values to test if there is no collision
        int _x = x, _y = y + 1;
        if (isTest)
            return GetAllPoints(_x, _y, currentState);
        
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
        states[2] = {
                    {0, 0, 0, 0},
                    {0, 0, 0, 0},
                    {1, 1, 1, 1},
                    {0, 0, 0, 0},
                    };
        states[3] = {
                    {0, 1, 0, 0},
                    {0, 1, 0, 0},
                    {0, 1, 0, 0},
                    {0, 1, 0, 0},
                    };        
    }
    
    vector<pair<int,int>> ClockWiseRotate(bool isTest = false) {
        int _currentState = currentState + 1;
        _currentState %= states.size();
        
        if (isTest)
            return GetAllPoints(x, y + 1, _currentState);
        
        currentState = _currentState;
        y++;
        return GetAllPoints(x, y, currentState);
    }; 
    vector<pair<int,int>> AntiClockWiseRotate(bool isTest = false) {
        int _currentState = currentState + 3;
        _currentState %= states.size();
        
        if (isTest)
            return GetAllPoints(x, y + 1, _currentState);
        
        currentState = _currentState;
        y++;
        return GetAllPoints(x, y, currentState);
    };
    vector<pair<int,int>> GoDown(bool isTest = false) {
        // When isTest is true -> does not update x and y values to test if there is no collision
        int _x = x, _y = y + 1;
        if (isTest)
            return GetAllPoints(_x, _y, currentState);
        
        x = _x; y = _y;
        return GetAllPoints();
    }
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
    }
    
    vector<pair<int,int>> ClockWiseRotate(bool isTest = false) {
        int _currentState = currentState + 1;
        _currentState %= states.size();
        
        if (isTest)
            return GetAllPoints(x, y + 1, _currentState);
        
        currentState = _currentState;
        y++;
        return GetAllPoints(x, y, currentState);
    }; 
    vector<pair<int,int>> AntiClockWiseRotate(bool isTest = false) {
        int _currentState = currentState + 3;
        _currentState %= states.size();
        
        if (isTest)
            return GetAllPoints(x, y + 1, _currentState);
        
        currentState = _currentState;
        y++;
        return GetAllPoints(x, y, currentState);
    };
    vector<pair<int,int>> GoDown(bool isTest = false) {
        // When isTest is true -> does not update x and y values to test if there is no collision
        int _x = x, _y = y + 1;
        if (isTest)
            return GetAllPoints(_x, _y, currentState);
        
        x = _x; y = _y;
        return GetAllPoints();
    };
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
    }
    
    vector<pair<int,int>> ClockWiseRotate(bool isTest = false) {
        int _currentState = currentState + 1;
        _currentState %= states.size();
        
        if (isTest)
            return GetAllPoints(x, y + 1, _currentState);
        
        currentState = _currentState;
        y++;
        return GetAllPoints(x, y, currentState);
    }; 
    vector<pair<int,int>> AntiClockWiseRotate(bool isTest = false) {
        int _currentState = currentState + 3;
        _currentState %= states.size();
        
        if (isTest)
            return GetAllPoints(x, y + 1, _currentState);
        
        currentState = _currentState;
        y++;
        return GetAllPoints(x, y, currentState);
    };
    vector<pair<int,int>> GoDown(bool isTest = false) {
        // When isTest is true -> does not update x and y values to test if there is no collision
        int _x = x, _y = y + 1;
        if (isTest)
            return GetAllPoints(_x, _y, currentState);
        
        x = _x; y = _y;
        return GetAllPoints();
    };
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
    }
    
    vector<pair<int,int>> ClockWiseRotate(bool isTest = false) {
        int _currentState = currentState + 1;
        _currentState %= states.size();
        
        if (isTest)
            return GetAllPoints(x, y + 1, _currentState);
        
        currentState = _currentState;
        y++;
        return GetAllPoints(x, y, currentState);
    }; 
    vector<pair<int,int>> AntiClockWiseRotate(bool isTest = false) {
        int _currentState = currentState + 3;
        _currentState %= states.size();
        
        if (isTest)
            return GetAllPoints(x, y + 1, _currentState);
        
        currentState = _currentState;
        y++;
        return GetAllPoints(x, y, currentState);
    };
    vector<pair<int,int>> GoDown(bool isTest = false) {
        // When isTest is true -> does not update x and y values to test if there is no collision
        int _x = x, _y = y + 1;
        if (isTest)
            return GetAllPoints(_x, _y, currentState);
        
        x = _x; y = _y;
        return GetAllPoints();
    };
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
    }
    
    
    vector<pair<int,int>> ClockWiseRotate(bool isTest = false) {
        int _currentState = currentState + 1;
        _currentState %= states.size();
        
        if (isTest)
            return GetAllPoints(x, y + 1, _currentState);
        
        currentState = _currentState;
        y++;
        return GetAllPoints(x, y, currentState);
    }; 
    vector<pair<int,int>> AntiClockWiseRotate(bool isTest = false) {};
    vector<pair<int,int>> GoDown(bool isTest = false) {
        // When isTest is true -> does not update x and y values to test if there is no collision
        int _x = x, _y = y + 1;
        if (isTest)
            return GetAllPoints(_x, _y, currentState);
        
        x = _x; y = _y;
        return GetAllPoints();
    };
};
