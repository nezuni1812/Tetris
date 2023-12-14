#include "Board.h"

Board::Board(){
    rows = 20;
    cols = 10;
    cellSize = 30;
    board = vector<vector<bool>>(20, (vector<bool>(10, 0)));
    
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

void Board::draw(){
    system("cls");
    vector<vector<bool>> toDraw(20, vector<bool>(10, 0));

    // Transfer all points in board to toDraw matrix 
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++){
            if(board[i][j] == 1)
                toDraw[i][j] = 1;
            // else if(board[i][j] == 2)
            //     toDraw[i][j] = 2;
        }
    }
    
    // Transfer all points in block b to toDraw matrix
    vector<pair<int,int>> pos = b->GetAllPoints();
    
    for (int i = 0; i < pos.size(); i++) {
        toDraw[pos[i].first][pos[i].second] = true;
        //toDraw[posGhost[i].first][posGhost[i].second] = false;
    }

    pos = b->drawGhostTetromino(board);
    for (int i = 0; i < pos.size(); i++) {
        toDraw[pos[i].first][pos[i].second] = true;
    }

    // Paint the toDraw matrix out
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++){
            cout << (j == 0 ? to_string(i%10) : "") << (toDraw[i][j] ? "#" : " ") << (j == 9 ? "." : ""); 
        }
        cout << "\n";
    }
    
    cout << "\n";
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

void Board::update(){
    int n;
    // cout << "(1) for Left, (3) for Right, (5) to Transform clockwise, (6) to Transform anti clock wise: ";
    int key = -1;
            
    // A non blocking input (If there is no input -> skip and go to next line)
    if (_kbhit()){
        key = _getch();
        // cout << "Key: " << key << "\n";
    }
    
    if (key == 0 || key == 224)
        key = _getch();
    
    bool result;
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
        case 32:
            cout << "Fully drop the block";
            b->hardDrop(board);
    }
    
    b->Continue(board);
    // if (reDraw)
    //     cin >> reDraw;
            
    // If the Tetriminos cannot go down anymore -> Merge it with the board + Create new Tetrimino
    if (b->cannotGoDown) {
        cout << "Creating new block\n";
        vector<pair<int,int>> pos = b->GetAllPoints();
        for (int i = 0; i < pos.size(); i++)
            board[pos[i].first][pos[i].second] = true;
        newTetriminos(); 
        b->drawGhostTetromino(board);
        if(b->isCollided(board, b->x, b->y, b->currentRotation)){
            isOver();
            cout << "Game over" << endl;
            exit(1);
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
        if(board[row][col] == 0)
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
    if(b->cannotGoDown && b->y <= 0)
        return true;
    return false;
}

