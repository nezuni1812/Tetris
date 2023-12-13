#include "Board.cpp"

int main(){
    Board board = Board();
    board.draw();
    while (1) {
        board.update();
        board.draw(); 
        cout << endl << endl;
    }
    
    return 0;
}