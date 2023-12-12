#include "Block.h"

bool Tetriminos::isCollided(vector<vector<bool>> board, int _x, int _y, int _currentState){
    vector<pair<int,int>> pos = GetAllPoints(_x, _y, _currentState);
    
    for (int i = 0; i < pos.size(); i++) {
        cout << pos[i].first << ", " << pos[i].second << endl;
        if (pos[i].first >= HEIGHT || pos[i].first < 0 || 
            pos[i].second >= WIDTH || pos[i].second < 0 ||
            board[pos[i].first][pos[i].second] != 0) {
                cout << "Cant go\n";
                return true;
            }
    }
            
    return false;
}

void Tetriminos::ClockWiseRotate(vector<vector<bool>> board) {
    int _currentState = currentState + 1;
    _currentState %= states.size();
    
    bool checkCollision = isCollided(board, x, y, _currentState);
    
    if (checkCollision)
        return ;
    
    currentState = _currentState;
}; 

bool Tetriminos::GoDown(vector<vector<bool>> board) {
    int _x = x, _y = y + 1;
    bool checkCollision = isCollided(board, _x, _y, currentState);
    
    if (checkCollision)
        return false;
    
    x = _x; y = _y;
    return true;
};

bool Tetriminos::GoLeft(vector<vector<bool>> board) {
    int _x = x - 1, _y = y;
    bool checkCollision = isCollided(board, _x, _y, currentState);
    
    if (checkCollision)
        return false;
    
    cout << "Go left\n";
    x = _x; y = _y;
    return true;
}; 

bool Tetriminos::GoRight(vector<vector<bool>> board) {
    int _x = x + 1, _y = y;
    bool checkCollision = isCollided(board, _x, _y, currentState);
    
    if (checkCollision)
        return false;
    
    cout << "Go right\n";
    x = _x; y = _y;
    return true;
};  

vector<pair<int,int>> Tetriminos::GetAllPoints(int _x = -100, int _y = -100, int _currentState = -100) {
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