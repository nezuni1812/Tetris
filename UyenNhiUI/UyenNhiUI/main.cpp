#include "Board.h"
#include "Block.h"
#include "Menu.h"
#include "Player.h"

int main()
{
    //Tạo ra cửa sổ window có kích cỡ 750x850
    RenderWindow window(VideoMode(750, 850), "Tetris", Style::Titlebar | Style::Close);
    vector<Player> list = inputPlayerInfo();
    displayLoginScreen(window, list);

    return 0;
}