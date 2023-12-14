#include "Board.h"

Board::Board(){
    rows = 20;
    cols = 10;
    cellSize = 30;
    board = vector<vector<Pixel>>(20, (vector<Pixel>(10, 0)));
    
    // For testing S spin
    board[18] = {1, 1, 1, 1, 1, 0, 0, 1, 1, 1};
    board[19] = {1, 1, 1, 1, 0, 0, 1, 1, 1, 1};
    // createBoard();

}

void Board::createBoard(){
    // for(int row = 0; row < rows; row++){
    //     for(int col = 0; col < cols; col++){
    //         board[row][col] = 0;
    //     }
    // }
}

void Board::print(){
    // for(int row = 0; row < rows; row++){
    //     for(int col = 0; col < cols; col++){
    //         cout << board[row][col];
    //     }
    //     cout << "\n";
    // }
}

vector<vector<Pixel>> Board::draw(bool drawOut = false){
    vector<vector<Pixel>> toDraw(20, vector<Pixel>(10, 0));

    // Transfer all points in board to toDraw matrix 
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 10; j++)
            if (board[i][j].filled == 1) {
                toDraw[i][j] = board[i][j];
            }
    }
    
    // Transfer all points in block b to toDraw matrix
    vector<pair<int,int>> pos = b->GetAllPoints(initialx,initialy,currentRotation);
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

void Board::newTetriminos() {
    if (b)
        delete b;

    srand(time(0));  
    int val = rand()% 7;

    
    switch (val)
    {
    case 0:
        b = new O;
        break;
        
    case 1:
        b = new I;
        break;
        
    case 2:
        b = new L;
        break;
        
    case 3:
        b = new J;
        break;
        
    case 4:
        b = new S;
        break;
        
    case 5:
        b = new T;
        break;
        
    case 6:
        b = new Z;
        break;
    
    default:
        break;
    }
    
}

void Board::update(string move = "update") {
    int key = -1;
            
    // A non blocking input (If there is no input -> skip and go to next line)
    if (_kbhit()){
        key = _getch();
        // cout << "Key: " << key << "\n";
    }
    
    if (move == "" && key == 0 || key == 224)
        key = _getch();

    if (move == "left")
        b->GoLeft(board);
    else if (move == "right")
        b->GoRight(board);
    else if (move == "down")
        b->GoDown(board);
    else if (move == "clock")
        b->Rotate(board, true);
    else if (move == "anticlock")
        b->Rotate(board, false);
    
    switch (key) {
        case 75:
            cout << "Case 1\n";
            b->GoLeft(board);
            break;
            
        case 77:
            cout << "Case 3\n";
            b->GoRight(board);
            break;
            
        case 72:
            cout << "Flip clock wise\n";
            b->Rotate(board, 1);
            break;
            
        case 80:
            cout << "Go down\n";
            b->GoDown(board);
            break;

        case 6:
            cout << "Flip anti clock wise\n";
            b->Rotate(board, 0);
            break;

    }
    
    b->Continue(board);
    // if (reDraw)
    //     cin >> reDraw;
            
    // If the Tetriminos cannot go down anymore -> Merge it with the board + Create new Tetrimino
    if (b->cannotGoDown) {
        vector<pair<int,int>> pos = b->GetAllPoints(initialx, initialy, currentRotation);

        for (int i = 0; i < pos.size(); i++) {
            board[pos[i].first][pos[i].second] = true;
            board[pos[i].first][pos[i].second].color = b->GetColor();
        }

        cout << "Creating new block\n";
        newTetriminos(); 
        if(b->isCollided(board, b->x, b->y, b->currentRotation)){
            overState = true;
            cout << "Game over" << endl;
        }
    }
    

    int lineDeleted = clearFullRows();
    draw();
    cout << "Score: " << updateScore(lineDeleted) << endl;
    
    if (b->timeSinceEpochMillisec() - updateTime > 1000) {
        updateTime = b->timeSinceEpochMillisec();
    }
    //cout << score(lineDeleted) << "\n";

   
    
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
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3: 
            score += 500;
            break;
        default:
            break;
    }
    return score;
}

bool Board::isOver(){
    return overState;
}