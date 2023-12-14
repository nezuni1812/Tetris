#include "Menu.h"
#include "Board.h"

void displayLoseScreen(sf::RenderWindow& window, int score = 0) {
    // Load and display the "Lose" screen image
    sf::Texture gameOverTexture;
    gameOverTexture.loadFromFile("Resources/lose_screen.png");

    sf::Sprite gameOver(gameOverTexture);
    window.draw(gameOver);
    window.display();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    return;
                }
            }
        }
    }
}

// Function to display the Play screen
void displayPlayScreen(sf::RenderWindow& window) {
    // Load and display the "Play" screen image
    const int LEFTPADDING = 43;
    const int TOPPADDING = 25;

    sf::Texture playScreenTexture;
    playScreenTexture.loadFromFile("Resources/game_screen.png");
    sf::Sprite playScreen(playScreenTexture);
    window.clear();

    Board board;

    vector<sf::Texture> blockTexture;
    blockTexture.resize(8);
    blockTexture[0].loadFromFile("Resources/grey.png");
    blockTexture[1].loadFromFile("Resources/cyan.png");
    blockTexture[2].loadFromFile("Resources/blue.png");
    blockTexture[3].loadFromFile("Resources/amber.png");
    blockTexture[4].loadFromFile("Resources/green.png");
    blockTexture[5].loadFromFile("Resources/purple.png");
    blockTexture[6].loadFromFile("Resources/red.png");
    blockTexture[7].loadFromFile("Resources/yellow.png");
    sf::Sprite singleBlock;
    sf::Sprite singleGhostBlock;

    while (window.isOpen()) {
        window.draw(playScreen);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    return;
                }

                else if (event.key.code == sf::Keyboard::Left) {
                    board.update("left");
                }

                else if (event.key.code == sf::Keyboard::Right) {
                    board.update("right");
                }

                else if (event.key.code == sf::Keyboard::Down) {
                    board.update("down");
                }

                else if (event.key.code == sf::Keyboard::Space) {
                    board.update("drop");
                }

                else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::J) {
                    board.update("clock");
                }

                else if (event.key.code == sf::Keyboard::K) {
                    board.update("anticlock");
                }
            }


        }

        board.update("update");

        vector<vector<Pixel>> tetrisStack = board.draw(false);

        for (int row = 0; row < tetrisStack.size(); row++)
            for (int col = 0; col < tetrisStack[row].size(); col++)
                if (tetrisStack[row][col].filled) {
                    cout << row << ", " << col << tetrisStack[row][col].color << endl;
                    singleBlock.setTexture(blockTexture[tetrisStack[row][col].color]);
                    singleBlock.setPosition(LEFTPADDING + 40*col, TOPPADDING + 40*row);
                    window.draw(singleBlock);
                }

        tetrisStack = board.drawGhostPiece();

        for (int row = 0; row < tetrisStack.size(); row++)
            for (int col = 0; col < tetrisStack[row].size(); col++)
                if (tetrisStack[row][col].filled) {
                    cout << row << ", " << col << tetrisStack[row][col].color << endl;
                    singleGhostBlock.setTexture(blockTexture[tetrisStack[row][col].color]);
                    singleGhostBlock.setColor(sf::Color(255,255,255,100));
                    singleGhostBlock.setPosition(LEFTPADDING + 40 * col, TOPPADDING + 40 * row);
                    window.draw(singleGhostBlock);
                }

        if (board.isOver())
            break;
        window.display();
    }

    //Move to Lose screen
    displayLoseScreen(window);
}


// Function to display the Instruction screen
void displayInstructionScreen(sf::RenderWindow& window) {
    // Load and display the "Instruction" screen image
    sf::Texture instructionScreenTexture;
    instructionScreenTexture.loadFromFile("Resources/instruction.png");
    sf::Sprite instructionScreen(instructionScreenTexture);
    window.draw(instructionScreen);
    window.display();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    return;
                }
            }
        }
    }
}

// Compare score 
bool comparePoint(Player& a, Player& b) {
    return a.getPoint() > b.getPoint();
}

// Function to display the Leaderboard screen
void displayLeaderboardScreen(sf::RenderWindow& window, vector<Player> list) {
    // Load and display the "Leaderboard" screen image
    sf::Texture leaderboardScreenTexture;
    leaderboardScreenTexture.loadFromFile("Resources/leaderboard.png");
    sf::Sprite leaderboardScreen(leaderboardScreenTexture);

    int size = 5;
    // Load font
    sf::Font fontPlay;
    fontPlay.loadFromFile("Resources/level-up.otf");

    // NUM
    std::vector<sf::Text> index(size);
    for (int i = 0; i < size; i++) {
        index[i].setFont(fontPlay);
        index[i].setString(to_string(i + 1) + ".");
        index[i].setCharacterSize(30);
        index[i].setFillColor(sf::Color(76, 37, 1, 255));
        index[i].setPosition(70, 330 + i * 50);
    }
    window.clear(sf::Color::Black);

    // NAME
    sort(list.begin(), list.end(), comparePoint);
    std::vector<sf::Text> NamePlayer(size);
    for (int i = 0; i < size; i++) {
        NamePlayer[i].setFont(fontPlay);
        NamePlayer[i].setString(list[i].getName());
        NamePlayer[i].setCharacterSize(30);
        NamePlayer[i].setFillColor(sf::Color(76, 37, 1, 255));
        NamePlayer[i].setPosition(125, 330 + i * 50);
    }
    window.clear(sf::Color::Black);

    // SCORE
    sort(list.begin(), list.end(), comparePoint);
    std::vector<sf::Text> ScorePlayer(size);
    for (int i = 0; i < size; i++) {
        ScorePlayer[i].setFont(fontPlay);
        ScorePlayer[i].setString(to_string(list[i].getPoint()));
        ScorePlayer[i].setCharacterSize(30);
        ScorePlayer[i].setFillColor(sf::Color(76, 37, 1, 255));
        ScorePlayer[i].setPosition(550, 330 + i * 50);
    }

    // Draw title screen image    
    window.draw(leaderboardScreen);

    // Draw leaderboard info
    for (int i = 0; i < size; ++i) {
        window.draw(index[i]);
        window.draw(NamePlayer[i]);
        window.draw(ScorePlayer[i]);
    }

    window.display();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    return;
                }
            }
        }
    }
}

void titleScreen(RenderWindow& window) {
    Texture* titleScreenTexture = new Texture();
    titleScreenTexture->loadFromFile("Resources/menu.png");
    Sprite titleScreen(*titleScreenTexture);

    //Inline initialize vector
    vector<Player> list = inputPlayerInfo();

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
                        displayPlayScreen(window);
                        break;
                    case 1:
                        displayLeaderboardScreen(window, list);
                        break;
                    case 2:
                        displayInstructionScreen(window);
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