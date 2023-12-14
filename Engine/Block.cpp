#include "Block.h"

Tetriminos::Tetriminos(int x, int y) : x(x), y(y) {
    lastUpdate = timeSinceEpochMillisec();
};

bool Tetriminos::isCollided(vector<vector<bool>> board, int _x, int _y, int _currentState){
    vector<pair<int,int>> pos = GetAllPoints(_x, _y, _currentState);
    
    for (int i = 0; i < pos.size(); i++) {
        // cout << pos[i].first << ", " << pos[i].second << endl;
        if (pos[i].first >= HEIGHT || pos[i].first < 0 || 
            pos[i].second >= WIDTH || pos[i].second < 0 ||
            board[pos[i].first][pos[i].second] != 0) {
                // cout << "Cant go\n";
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

uint64_t Tetriminos::timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void Tetriminos::LastUpdate() {
    lastUpdate = timeSinceEpochMillisec();
}

bool Tetriminos::Continue(vector<vector<bool>> board) {
    unsigned long long timeNow = timeSinceEpochMillisec();
    // cout << (timeNow - lastUpdate) << " time has passed\n";
    if ((timeNow - lastUpdate) < 400)
        return false;
        
    if (!GoDown(board))
        cannotGoDown = true;
            
    lastUpdate = timeSinceEpochMillisec();
    // cout << "Updated time\n";
    // int n;
    // cin >> n;
    return true;
}

void Tetriminos::Rotate(vector<vector<bool>> board, bool clockWise) {
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

bool Tetriminos::GoDown(vector<vector<bool>> board) {
    int _x = x, _y = y + 1;
    
    if (isCollided(board, _x, _y, currentRotation)) {
        return false;
    }
    
    x = _x; y = _y;
    return true;
};

bool Tetriminos::GoLeft(vector<vector<bool>> board) {
    int _x = x - 1, _y = y;
    
    if (isCollided(board, _x, _y, currentRotation))
        return false;
    
    cout << "Go left\n";
    x = _x; y = _y;
    return true;
}; 

bool Tetriminos::GoRight(vector<vector<bool>> board) {
    int _x = x + 1, _y = y;
    
    if (isCollided(board, _x, _y, currentRotation))
        return false;
    
    cout << "Go right\n";
    x = _x; y = _y;
    return true;
};  

void Tetriminos::hardDrop(vector<vector<bool>> board){  
    while(GoDown(board)){
        if(isCollided(board, x, y, currentRotation))
            break;
    }
}

vector<pair<int,int>> Tetriminos::GetAllPoints(int _x = -100, int _y = -100, int _currentRotation = -100) {
    if (_x == -100) {
        _x = x;
        _y = y;
        _currentRotation = currentRotation;
    }
    
    vector<pair<int,int>> points;
    for (int i = 0; i < states[_currentRotation].size(); i++)
        for (int j = 0; j < states[_currentRotation][0].size(); j++)
            if (states[_currentRotation][i][j])
                points.push_back(make_pair(_y + i, _x + j));
            
    return points;
}

vector<pair<int,int>> Tetriminos::drawGhostTetromino(vector<vector<bool>> board) {
    int ghostY = y;

    while (!isCollided(board, x, ghostY + 1, currentRotation)) {
        ghostY++;
    }

    vector<pair<int, int>> ghostPoints = GetAllPoints(x, ghostY, currentRotation);
    return ghostPoints;
}



