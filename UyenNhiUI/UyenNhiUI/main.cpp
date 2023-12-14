#include "Board.h"
#include "Block.h"
#include "Menu.h"
#include "Player.h"

int main() {
    Board board = Board();
    board.draw();
    while (1) {
        board.update();
        // cout << endl << endl;
    }
}

/*
int main() {
    Music music;
    music.openFromFile("Resources/intro.wav");

    RenderWindow window(VideoMode(750, 850), "Tetris", Style::Titlebar | Style::Close);
    titleScreen(window);
}
*/