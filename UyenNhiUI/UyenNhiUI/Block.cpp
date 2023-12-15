#include "Block.h"

Tetriminos::Tetriminos(int x, int y, int color, char type) : x(x), y(y), color(color), type(type) {
    lastUpdate = timeSinceEpochMillisec();
};

bool Tetriminos::isCollided(vector<vector<Pixel>> board, int _x, int _y, int _currentState){
    vector<pair<int,int>> pos = GetAllPoints(_x, _y, _currentState);
    
    for (int i = 0; i < pos.size(); i++) {
        if (pos[i].first >= HEIGHT || pos[i].first < 0 || 
            pos[i].second >= WIDTH || pos[i].second < 0 ||
            board[pos[i].first][pos[i].second].filled != 0) {
                return true;
            }
    }
            
    return false;
}

bool Tetriminos::isObstructedDown() {
    return cannotGoDown;
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

void Tetriminos::SetColor() {
    for (int i = 0; i < states.size(); i++)
        for (int j = 0; j < states[i].size(); j++)
            for (int z = 0; z < states[i][j].size(); z++)
                states[i][j][z].color = color;
}
void Tetriminos::SetWaitTime(int wait) {
    if (wait <= 1)
        this->waitTime = 1200;
    else if (wait <= 2)
        this->waitTime = 900;
    else if (wait <= 3)
        this->waitTime = 600;
    else
        this->waitTime = 290;

}

uint64_t Tetriminos::timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

bool Tetriminos::Continue(vector<vector<Pixel>> board) {
    unsigned long long timeNow = timeSinceEpochMillisec();
    if ((timeNow - lastUpdate) < waitTime)
        return false;
        
    if (!GoDown(board))
        cannotGoDown = true;
            
    lastUpdate = timeSinceEpochMillisec();
    return true;
}

void Tetriminos::Rotate(vector<vector<Pixel>> board, bool clockWise) {
    int nextRotation;
    if (clockWise)
        nextRotation = currentRotation + 1;
    else
        nextRotation = currentRotation + states.size() - 1;
        
    nextRotation %= states.size();
    
    bool checkCollision;
    int testCase;
    for (testCase = 0; testCase < wallKickCase[currentRotation][nextRotation].size(); testCase++) {
        int offSetY = wallKickCase[currentRotation][nextRotation][testCase].first;
        int offSetX = wallKickCase[currentRotation][nextRotation][testCase].second;
        cout << "Offset: " << offSetY << " " << offSetX << endl;
        checkCollision = isCollided(board, x + offSetX, y - offSetY, nextRotation);
        if (!checkCollision)
            break;
    }
    
    if (checkCollision)
        return ;
    cout << "Case " << testCase << endl;
    y = y - wallKickCase[currentRotation][nextRotation][testCase].first;
    x = x + wallKickCase[currentRotation][nextRotation][testCase].second;
    currentRotation = nextRotation;
}; 

bool Tetriminos::GoDown(vector<vector<Pixel>> board) {
    int _x = x, _y = y + 1;
    
    if (isCollided(board, _x, _y, currentRotation)) {
        return false;
    }
    
    x = _x; y = _y;
    return true;
};

bool Tetriminos::HardDrop(vector<vector<Pixel>> board) {
    while (GoDown(board)) {
        if (isCollided(board, x, y, currentRotation)) {
            return true;
        }
    }
    cannotGoDown = true;
    return false;
}

bool Tetriminos::GoLeft(vector<vector<Pixel>> board) {
    int _x = x - 1, _y = y;
    
    if (isCollided(board, _x, _y, currentRotation))
        return false;
    
    cout << "Go left\n";
    x = _x; y = _y;
    return true;
}; 

bool Tetriminos::GoRight(vector<vector<Pixel>> board) {
    int _x = x + 1, _y = y;
    
    if (isCollided(board, _x, _y, currentRotation))
        return false;
    
    cout << "Go right\n";
    x = _x; y = _y;
    return true;
};  

int Tetriminos::GetX() {
    return x;
}
int Tetriminos::GetY() {
    return y;
}
int Tetriminos::GetCurrentRotation() {
    return currentRotation;
}

//Return position of each filled pixel of a block in x, y coordinate
vector<pair<int,int>> Tetriminos::GetAllPoints(int _x, int _y, int _currentRotation) {
    if (_x == -100) {
        _x = x;
        _y = y;
        _currentRotation = currentRotation;
    }
    
    vector<pair<int,int>> points;
    for (int i = 0; i < states[_currentRotation].size(); i++)
        for (int j = 0; j < states[_currentRotation][0].size(); j++)
            if (states[_currentRotation][i][j].filled)
                points.push_back(make_pair(_y + i, _x + j));
            
    return points;
}

vector<pair<int, int>> Tetriminos::GetGhostTetrominoPoints(vector<vector<Pixel>> board) {
    int ghostY = y;

    while (!isCollided(board, x, ghostY + 1, currentRotation)) {
        ghostY++;
    }

    vector<pair<int, int>> ghostPoints = GetAllPoints(x, ghostY, currentRotation);
    return ghostPoints;
}

int Tetriminos::GetColor() {
    return color;
}
char Tetriminos::GetType() {
    return type;
}