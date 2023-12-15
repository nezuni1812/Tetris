#include "Board.h"

Board::Board(bool hardMode) {
    rows = 20;
    cols = 10;
    cellSize = 30;
    this->hardMode = hardMode;
    board = vector<vector<Pixel>>(20, (vector<Pixel>(10, 0)));
    startTime = timeSinceEpochMillisec();

    if (hardMode)
        changeExistingStack();

    newTetriminos();
    b = nextTetromino;
    newTetriminos();
    b->SetWaitTime(1);
}

uint64_t Board::timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch()).count();
}

vector<vector<Pixel>> Board::draw(bool drawOut = false){
    vector<vector<Pixel>> toDraw(20, vector<Pixel>(10, 0));

    // Transfer all points in board to toDraw matrix 
    toDraw = board;

    // Transfer all points in current tetromino to toDraw matrix
    vector<pair<int,int>> pos = b->GetAllPoints();
    for (int i = 0; i < pos.size(); i++) {
        toDraw[pos[i].first][pos[i].second].filled = true;
        toDraw[pos[i].first][pos[i].second].color = b->GetColor();
    }

    // Paint the toDraw matrix out
    if (drawOut) {
        system("cls");
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 10; j++)
                cout << (j == 0 ? to_string(i % 10) : "") << (toDraw[i][j].filled ? "#" : " ") << (j == 9 ? "." : "");
            cout << "\n";
        }
        cout << "\n";
    }
    
    
    return toDraw;
}

vector<vector<Pixel>> Board::drawGhostPiece() {
    vector<vector<Pixel>> toDraw = board;

    vector<pair<int, int>> pos = b->GetGhostTetrominoPoints(board);
    for (int i = 0; i < pos.size(); i++) {
        toDraw[pos[i].first][pos[i].second].filled = true;
        toDraw[pos[i].first][pos[i].second].color = b->GetColor();
    }

    return toDraw;
}

void Board::newTetriminos() {
    srand(time(0));  
    int val = rand()% 7;

    
    switch (val)
    {
    case 0:
        nextTetromino = new O;
        break;
        
    case 1:
        nextTetromino = new I;
        break;
        
    case 2:
        nextTetromino = new L;
        break;
        
    case 3:
        nextTetromino = new J;
        break;
        
    case 4:
        nextTetromino = new S;
        break;
        
    case 5:
        nextTetromino = new T;
        break;
        
    case 6:
        nextTetromino = new Z;
        break;
    
    default:
        break;
    }
    
}

void Board::updateBlockWaitTime() {
    if (score < 20)
        b->SetWaitTime(1);
    else if (score < 50)
        b->SetWaitTime(2);
    else if (score < 80)
        b->SetWaitTime(3);
    else
        b->SetWaitTime(4);
}

void Board::changeExistingStack() {
    int rowsToMessUp;
    if (score < 20)
        rowsToMessUp = 3;
    else if (score < 40)
        rowsToMessUp = 5;
    else if (score < 70)
        rowsToMessUp = 6;
    else
        rowsToMessUp = 10;

    for (int i = 0; i < rowsToMessUp; i++){
        board[rows - 1 - i] = vector<Pixel>(10, 1);

        int missingSpot = rand()%2 + 1;
        for (int j = 0; j < missingSpot; j++)
            board[rows - 1 - i][rand()%10] = Pixel(0);
    }
}


void Board::update(string move = "update") {

    if (move == "left")
        b->GoLeft(board);
    else if (move == "right")
        b->GoRight(board);
    else if (move == "down")
        b->GoDown(board);
    else if (move == "drop")
        b->HardDrop(board);
    else if (move == "clock")
        b->Rotate(board, true);
    else if (move == "anticlock")
        b->Rotate(board, false);
    
    b->Continue(board);
            
    // If the Tetriminos cannot go down anymore -> Merge it with the board + Create new Tetromino + Check if the game is over
    if (b->isObstructedDown()) {
        vector<pair<int,int>> pos = b->GetAllPoints();

        for (int i = 0; i < pos.size(); i++) {
            board[pos[i].first][pos[i].second] = true;
            board[pos[i].first][pos[i].second].color = b->GetColor();
        }

        cout << "Creating new block\n";
        if (b)
            delete b;
        b = nextTetromino;
        newTetriminos(); 

        if (score < 20)
            b->SetWaitTime(1);
        else if (score < 50)
            b->SetWaitTime(2);
        else if (score < 80)
            b->SetWaitTime(3);
        else
            b->SetWaitTime(4);

        if (b->isCollided(board, b->GetX(), b->GetY(), b->GetCurrentRotation())) {
            overState = true;
            cout << "Game over" << endl;
        }
    }
    

    int lineDeleted = clearFullRows();
    updateScore(lineDeleted);
    
    if (b->timeSinceEpochMillisec() - updateTime > 1000) {
        updateTime = b->timeSinceEpochMillisec();
    }
}

Tetriminos* Board::GetCurrentTetromino() {
    return b;
}

Tetriminos* Board::GetNextTetromino() {
    return nextTetromino;
}

int Board::GetPoints() {
    return score;
}

uint64_t Board::GetTimePlayed() {
    return timeSinceEpochMillisec() - startTime;
}

//clear row 
void Board::clearRow(int row){
    for(int col = 0; col < cols; col++)
        board[row][col] = 0;
}

//check if a row is full of blocks or not
bool Board::isRowFull(int row){
    for(int col = 0; col < cols; col++)
        if(board[row][col].filled == 0)
            return false;
    return true;
}

//remove the above row after a row is deleted
void Board::moveRowDown(int row, int rows){
    for(int col = 0; col < cols; col++){
        board[row + rows][col] = board[row][col];
        board[row][col] = 0;
    }
}

//delete a row using all 3 functions above
int Board::clearFullRows(){
    //delete_line.play();
    int completed = 0;
    for(int row = rows - 1; row >=0; row--){
        if(isRowFull(row)){
            clearRow(row);
            completed++;
        }
        else if(completed > 0){
            moveRowDown(row, completed);
        }
    }
    return completed;
}

int Board::updateScore(int lineDeleted){
    switch(lineDeleted){
        case 1:
            score += 10;
            break;
        case 2:
            score += 30;
            break;
        case 3: 
            score += 50;
            break;
        case 4:
            score += 65;
        default:
            break;
    }
    return score;
}

bool Board::isOver(){
    return overState;
}