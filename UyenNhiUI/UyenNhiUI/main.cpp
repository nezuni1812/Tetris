#include "Board.h"
#include "Block.h"
#include "Menu.h"
#include "Player.h"

//int mainh() {
//    Board board = Board();
//    board.draw(true);
//    while (1) {
//        board.update("right");
//        // cout << endl << endl;
//    }
//
//    return 0;
//}

int main()
{
    RenderWindow window(VideoMode(750, 850), "Tetris", Style::Titlebar | Style::Close);
    vector<Player> list = inputPlayerInfo();
    displayLoginScreen(window, list);

    return 0;
}