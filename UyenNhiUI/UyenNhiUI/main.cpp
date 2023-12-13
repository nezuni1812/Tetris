#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <Windows.h>

using namespace sf;
using namespace std;

enum class GameState : int {
    TitleScreen, Playing, GameOver, GameWon, Exit
};

const int MENU_ITEM_COUNT = 4;
const string MENU_ITEMS[MENU_ITEM_COUNT] = { "PLAY", "Leaderboard", "Instruction", "Exit" };

void titleScreen(RenderWindow& window) {
    Texture* titleScreenTexture = new Texture();
    titleScreenTexture->loadFromFile("Resources/menu.png");
    Sprite titleScreen(*titleScreenTexture);

    bool startGame = false;
    bool exit = false;

    // Create text objects for menu items
    sf::Text menuTexts[MENU_ITEM_COUNT];

    // Load font
    sf::Font fontPlay;
    fontPlay.loadFromFile("Resources/TypefaceMarioWorldPixelFilledRegular-rgVMx.ttf");

    //Cài đặt cho chữ Play
    menuTexts[0].setFont(fontPlay);
    menuTexts[0].setString(MENU_ITEMS[0]);
    menuTexts[0].setCharacterSize(30);
    menuTexts[0].setFillColor(sf::Color(76, 37, 1, 255));
    menuTexts[0].setPosition(326, 445);

    sf::Font font;
    font.loadFromFile("Resources/PixemonTrialRegular-p7nLK.ttf");
    menuTexts[1].setPosition(310, 537 + 0 * 65);
    menuTexts[2].setPosition(319, 537 + 1 * 65);
    menuTexts[3].setPosition(366, 537 + 2 * 65);

    for (int i = 1; i < MENU_ITEM_COUNT; ++i) {
        menuTexts[i].setFont(font);
        menuTexts[i].setString(MENU_ITEMS[i]);
        menuTexts[i].setCharacterSize(25);
        menuTexts[i].setFillColor(sf::Color(76, 37, 1, 255));
    }

    int selectedItem = 0; // Index of the currently selected menu item

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    selectedItem = (selectedItem - 1 + MENU_ITEM_COUNT) % MENU_ITEM_COUNT;
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    selectedItem = (selectedItem + 1) % MENU_ITEM_COUNT;
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    // Perform action based on the selected item
                    switch (selectedItem) {
                    case 0:
                        std::cout << "Play selected!" << std::endl;
                        break;
                    case 1:
                        std::cout << "Instruction selected!" << std::endl;
                        break;
                    case 2:
                        std::cout << "Leaderboard selected!" << std::endl;
                        break;
                    case 3:
                        std::cout << "Exit selected!" << std::endl;
                        window.close();
                        break;
                    }
                }
            }
        }

        // Update text color based on selection
        for (int i = 0; i < MENU_ITEM_COUNT; ++i) {
            menuTexts[i].setFillColor(i == selectedItem ? sf::Color::Red : sf::Color(76, 37, 1, 255));
        }

        window.clear(sf::Color::Black);

        // Draw title screen image
        window.draw(titleScreen);

        // Draw menu items
        for (int i = 0; i < MENU_ITEM_COUNT; ++i) {
            window.draw(menuTexts[i]);
        }

        window.display();
    }
}

int main()
{
    RenderWindow window(VideoMode(750, 850), "Tetris", Style::Titlebar | Style::Close);
    titleScreen(window);
}