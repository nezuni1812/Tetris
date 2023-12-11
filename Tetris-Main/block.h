#include <bits/stdc++.h>

using namespace std;
class Tetriminos {
public:
    Tetriminos(int x, int y) : x(x), y(y) {};
    int currentState = 0;
    int x = -1, y = -1;
    vector<vector<vector<bool>>> states;
    
    virtual bool ClockWiseRotate() = 0; 
    virtual bool AntiClockWiseRotate() = 0;
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
    
    bool ClockWiseRotate() {};
    bool TryClockWiseRotate() {};
    bool AntiClockWiseRotate() {};
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
    
    bool ClockWiseRotate() = 0; 
    bool AntiClockWiseRotate() = 0;
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
    Z(int x = 5, int y = 20) : Tetriminos(x, y) {
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
