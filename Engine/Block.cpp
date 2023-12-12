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

void Tetriminos::InitWallKick(int type) {
    wallKickCase.resize(4);
    
    for (int i = 0; i < wallKickCase.size(); i++) {
        wallKickCase[i].resize(4);
    }
    
    if (type == 0){
        wallKickCase[0][1]  =  {make_pair(0, 0), make_pair(0, -1), make_pair( 1, -1), make_pair(-2, 0), make_pair(-2, -1)};
        wallKickCase[1][0]  =  {make_pair(0, 0), make_pair(0,  1), make_pair(-1,  1), make_pair( 2, 0), make_pair( 2,  1)};
        wallKickCase[1][2]  =  {make_pair(0, 0), make_pair(0,  1), make_pair(-1,  1), make_pair( 2, 0), make_pair( 2,  1)};
        wallKickCase[2][1]  =  {make_pair(0, 0), make_pair(0, -1), make_pair( 1, -1), make_pair(-2, 0), make_pair(-2, -1)};
        wallKickCase[2][3]  =  {make_pair(0, 0), make_pair(0,  1), make_pair( 1,  1), make_pair(-2, 0), make_pair(-2,  1)};
        wallKickCase[3][2]  =  {make_pair(0, 0), make_pair(0, -1), make_pair(-1, -1), make_pair( 2, 0), make_pair( 2, -1)};
        wallKickCase[3][0]  =  {make_pair(0, 0), make_pair(0, -1), make_pair(-1, -1), make_pair( 2, 0), make_pair( 2, -1)};
        wallKickCase[0][3]  =  {make_pair(0, 0), make_pair(0,  1), make_pair( 1,  1), make_pair(-2, 0), make_pair(-2,  1)};
    }
    else {
        wallKickCase[0][1] = {make_pair(0, 0), make_pair(0, -2), make_pair(0,  1), make_pair(-1, -2), make_pair( 2,  1)};
        wallKickCase[1][0] = {make_pair(0, 0), make_pair(0,  2), make_pair(0, -1), make_pair( 1,  2), make_pair(-2, -1)};
        wallKickCase[1][2] = {make_pair(0, 0), make_pair(0, -1), make_pair(0,  2), make_pair( 2, -1), make_pair(-1,  2)};
        wallKickCase[2][1] = {make_pair(0, 0), make_pair(0,  1), make_pair(0, -2), make_pair(-2,  1), make_pair( 1, -2)};
        wallKickCase[2][3] = {make_pair(0, 0), make_pair(0,  2), make_pair(0, -1), make_pair( 1,  2), make_pair(-2, -1)};
        wallKickCase[3][2] = {make_pair(0, 0), make_pair(0, -2), make_pair(0,  1), make_pair(-1, -2), make_pair( 2,  1)};
        wallKickCase[3][0] = {make_pair(0, 0), make_pair(0,  1), make_pair(0, -2), make_pair(-2,  1), make_pair( 1, -2)};
        wallKickCase[0][3] = {make_pair(0, 0), make_pair(0, -1), make_pair(0,  2), make_pair( 2, -1), make_pair(-1,  2)};
    }
    
}

void Tetriminos::Rotate(vector<vector<bool>> board, bool clockWise) {
    int _currentState;
    if (clockWise)
        _currentState = currentState + 1;
    else
        _currentState = currentState + states.size() - 1;
        
    _currentState %= states.size();
    
    bool checkCollision;
    int i;
    for (i = 0; i < wallKickCase[currentState][_currentState].size(); i++) {
        int offSetY = wallKickCase[currentState][_currentState][i].first;
        int offSetX = wallKickCase[currentState][_currentState][i].second;
        cout << "Offset: " << offSetY << " " << offSetX << endl;
        checkCollision = isCollided(board, x + offSetX, y - offSetY, _currentState);
        cout << "End of check " << checkCollision << "\n";
        if (!checkCollision)
            break;
    }
    
    if (checkCollision)
        return ;
    
    cout << wallKickCase[currentState][_currentState][i].first << wallKickCase[currentState][_currentState][i].second << endl;
    y = y - wallKickCase[currentState][_currentState][i].first;
    x = x + wallKickCase[currentState][_currentState][i].second;
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