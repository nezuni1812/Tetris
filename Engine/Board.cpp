#include "board.h"

Board::Board(){
    rows = 20;
    cols = 10;
    cellSize = 30;
    
    board = vector<vector<bool>>(20, (vector<bool>(10, 0)));
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
    //     cout << endl;
    // }
}

void Board::draw(){
    vector<vector<bool>> toDraw(20, vector<bool>(10, 0));

    // Transfer all points in board to toDraw matrix 
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++)
            if(board[i][j] == 1)
                toDraw[i][j] = 1;
    }
    
    // Transfer all points in block b to toDraw matrix
    vector<pair<int,int>> pos = b->GetAllPoints();
    for (int i = 0; i < pos.size(); i++) {
        toDraw[pos[i].first][pos[i].second] = true;
    }

    // Paint the toDraw matrix out
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++)
            cout << (j == 0 ? "." : "") << (toDraw[i][j] ? "#" : " ") << (j == 9 ? "." : "");
        cout << endl;
    }
}

void Board::newTetriminos() {
    if (b)
        delete b;
    srand(time(0));  
    int val = rand()% 6;
    
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
        b = new S;
        break;
        
    case 4:
        b = new T;
        break;
        
    case 5:
        b = new Z;
        break;
    
    default:
        break;
    }
    
}

bool Board::isCollied(vector<pair<int,int>> pos){
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

void Board::update(){
    int n;
    cout << "(1) for Left, (3) for Right, (5) to Transform clockwise, (6) to Transform anti clock wise: ";
    cin >> n;
    
    bool result;
    switch (n) {
        case 1:
            cout << "Case 1\n";
            b->GoLeft(board);
            break;
            
        case 3:
            cout << "Case 3\n";
            b->GoRight(board);
            break;
            
        case 5:
            cout << "Flip clock wise\n";
            b->Rotate(board, 1);
            break;

        case 6:
            cout << "Flip anti clock wise\n";
            b->Rotate(board, 0);
            break;

    }
    
    if (true)
        if (!b->GoDown(board))
            b->cannotGoDown = true;
    
    // If the Tetriminos cannot go down anymore -> Merge it with the board + Create new Tetrimino
    if (b->cannotGoDown) {
        cout << "Creating new block\n";
        vector<pair<int,int>> pos = b->GetAllPoints();
        for (int i = 0; i < pos.size(); i++)
            board[pos[i].first][pos[i].second] = true;
        newTetriminos(); 
    }
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
void Board::clearFullRows(){
    int completed = 0;
    for(int row = row - 1; row >=0; row--){
        if(isRowFull(row)){
            clearRow(row);
            completed++;
            cout << "number of rows deleted: " << completed << endl;
        }
        else if(completed > 0){
            moveRowDown(row, completed);
        }
    }
}