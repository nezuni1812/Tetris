#include "Menu.h"
#include "Board.h"

void displayLoginScreen(RenderWindow& window, vector<Player>& list) {
    Texture loginTexture;
    loginTexture.loadFromFile("Resources/game_screen/login.png");
    Sprite login(loginTexture);

    sf::Font font;
    if (!font.loadFromFile("Resources/font/level-up.otf")) {
        cout << "Error loading font." << endl;
        return;
    }

    Text usernameText;
    usernameText.setFont(font);
    usernameText.setCharacterSize(27);
    usernameText.setFillColor(Color(76, 37, 1, 255));
    usernameText.setPosition(220, 337);

    Text sign;
    sign.setFont(font);
    sign.setCharacterSize(22);
    sign.setFillColor(Color::Red);
    sign.setPosition(55, 400);

    string username;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 13) { // Enter key
                    // Check if username is not empty and does not exceed 15 characters
                    if (!username.empty() && username.length() <= 15) {
                        list.push_back(Player(username, 0, 0));
                        titleScreen(window, list);
                        return;
                    }
                    else if (username.length() > 15) {
                        sign.setPosition(55, 400);
                        sign.setString("Username should not exceed 15 characters!");
                    }
                    else if (username.empty()) {
                        sign.setPosition(148, 400);
                        sign.setString("Username should not be empty!");
                    }
                }
                else if (((event.text.unicode >= 48) && (event.text.unicode <= 57))
                    || ((event.text.unicode >= 65) && (event.text.unicode <= 90))
                    || ((event.text.unicode >= 97) && (event.text.unicode <= 122))) {
                    username += static_cast<char>(event.text.unicode);
                }
                else if (event.text.unicode == 8) { // Backspace
                    if (!username.empty()) {
                        username.pop_back();
                    }
                }

                usernameText.setString(username);
            }
        }
        window.clear();
        window.draw(login);
        window.draw(sign);
        window.draw(usernameText);
        window.display();
    }
}

void displayLoseScreen(RenderWindow& window, int score = 0) {
    // Load and display the "Lose" screen image
    Texture gameOverTexture;
    gameOverTexture.loadFromFile("Resources/game_screen/lose_screen.png");

    Font fontPlay;
    fontPlay.loadFromFile("Resources/font/level-up.otf");

    Music music;
    music.openFromFile("Resources/music/lose_game.wav");
    music.setVolume(35.0);
    music.setLoop(true);
    music.play();

    Text Score;
    Score.setFont(fontPlay);
    Score.setString("SCORE: " + to_string(score));
    Score.setCharacterSize(40);
    Score.setFillColor(Color(255, 245, 91, 255));
    Score.setPosition(239, 492);

    Sprite gameOver(gameOverTexture);
    window.draw(gameOver);
    window.draw(Score);
    window.display();
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    return;
                }
            }
        }
    }
}

string displayChooseMode(RenderWindow& window) {
    Texture chooseModeTexture;
    chooseModeTexture.loadFromFile("Resources/game_screen/choose_mode.png");
    Sprite chooseMode(chooseModeTexture);

    Font fontPlay;
    fontPlay.loadFromFile("Resources/font/TypefaceMarioWorldPixelFilledRegular-rgVMx.ttf");

    Music music_move;
    music_move.openFromFile("Resources/music/move.wav");
    music_move.setVolume(35.0);

    Text mode[MODE_COUNT];
    for (int i = 0; i < MODE_COUNT; i++) {
        mode[i].setFont(fontPlay);
        mode[i].setString(MODE_CHOOSE[i]);
        mode[i].setCharacterSize(22);
        mode[i].setFillColor(Color(255, 245, 91, 255));
        mode[i].setPosition(327, 358 + i*78);
    }    

    int selectedItem = 0;

    while (window.isOpen()) {
        Event event;
        string res;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::KeyPressed) {
                music_move.play();
                if (event.key.code == Keyboard::Up) {
                    selectedItem = (selectedItem - 1 + MODE_COUNT) % MODE_COUNT;
                }
                else if (event.key.code == Keyboard::Down) {
                    selectedItem = (selectedItem + 1) % MODE_COUNT;
                }
                else if (event.key.code == Keyboard::Enter) {
                    switch (selectedItem) {
                    case 0: //Mode Easy
                        res = "EASY";
                        return res;
                    case 1: //Mode Hard
                        res = "HARD";
                        return res;
                    }
                }
            }
        }

        for (int i = 0; i < MODE_COUNT; ++i) {
            mode[i].setFillColor(i == selectedItem ? Color::Red : Color(76, 37, 1, 255));
        }
        window.draw(chooseMode);
        for (int i = 0; i < MODE_COUNT; i++) {
            window.draw(mode[i]);
        }
        window.display();
    }
}

// Function to display the Play screen
void displayPlayScreen(RenderWindow& window, string hardMode, vector<Player>& list) {
    // Load and display the "Play" screen image
    const int LEFTPADDING = 42;
    const int TOPPADDING = 25;

    Texture playScreenTexture;
    playScreenTexture.loadFromFile("Resources/game_screen/game_screen.png");
    Sprite playScreen(playScreenTexture);
    window.clear();

    Music music_play;
    music_play.openFromFile("Resources/music/play_background.wav");
    music_play.setLoop(true);
    music_play.setVolume(35.0);
    music_play.play();

    bool goHard = (hardMode == "HARD");
    Board board(goHard);

    vector<Texture> blockTexture;
    blockTexture.resize(8);
    blockTexture[0].loadFromFile("Resources/tetromino_texture/grey.png");
    blockTexture[1].loadFromFile("Resources/tetromino_texture/cyan.png");
    blockTexture[2].loadFromFile("Resources/tetromino_texture/blue.png");
    blockTexture[3].loadFromFile("Resources/tetromino_texture/amber.png");
    blockTexture[4].loadFromFile("Resources/tetromino_texture/green.png");
    blockTexture[5].loadFromFile("Resources/tetromino_texture/purple.png");
    blockTexture[6].loadFromFile("Resources/tetromino_texture/red.png");
    blockTexture[7].loadFromFile("Resources/tetromino_texture/yellow.png");
    Sprite singleBlock;
    Sprite singleGhostBlock;

    Font fontPlay;
    fontPlay.loadFromFile("Resources/font/level-up.otf");

    Music music_move;
    music_move.openFromFile("Resources/music/move.wav");
    music_move.setVolume(35.0);

    bool isPause = false;

    while (window.isOpen()) {
        window.draw(playScreen);
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            else if (event.type == Event::KeyPressed) {

                if (event.key.code == Keyboard::Escape) {
                    return;
                }

                else if (event.key.code == Keyboard::P) {
                    isPause = !isPause;
                }

                else if (event.key.code == Keyboard::Left) {
                    board.update("left");
                }

                else if (event.key.code == Keyboard::Right) {
                    board.update("right");
                }

                else if (event.key.code == Keyboard::Down) {
                    board.update("down");
                }

                else if (event.key.code == Keyboard::Space) {
                    board.update("drop");
                }

                else if (event.key.code == Keyboard::Up || event.key.code == Keyboard::K) {
                    music_move.play();
                    board.update("clock");
                }

                else if (event.key.code == Keyboard::J) {
                    music_move.play();
                    board.update("anticlock");
                }
            }


        }

        if (isPause) {
            window.display();
            continue;
        }

        board.update("update");

        vector<vector<Pixel>> tetrisStack = board.draw(false);
        for (int row = 0; row < tetrisStack.size(); row++)
            for (int col = 0; col < tetrisStack[row].size(); col++)
                if (tetrisStack[row][col].filled) {
                    singleBlock.setTexture(blockTexture[tetrisStack[row][col].color]);
                    singleBlock.setPosition(LEFTPADDING + 40*col, TOPPADDING + 40*row);
                    window.draw(singleBlock);
                }

        tetrisStack = board.drawGhostPiece();
        for (int row = 0; row < tetrisStack.size(); row++)
            for (int col = 0; col < tetrisStack[row].size(); col++)
                if (tetrisStack[row][col].filled) {
                    singleGhostBlock.setTexture(blockTexture[tetrisStack[row][col].color]);

                    singleGhostBlock.setColor(Color(255,255,255,100));

                    singleGhostBlock.setPosition(LEFTPADDING + 40 * col, TOPPADDING + 40 * row);
                    window.draw(singleGhostBlock);
                }

        //Next piece sprite
        string nextPieceFileName = "Resources/tetromino_texture/";
        nextPieceFileName += board.GetNextTetrominoType();
        nextPieceFileName += ".png";
        Texture nextPieceTexture;
        nextPieceTexture.loadFromFile(nextPieceFileName.c_str());
        Sprite nextImage;
        nextImage.setTexture((nextPieceTexture));
        nextImage.setPosition(502, 80);
        window.draw(nextImage);

        Text uiText;
        uiText.setFont(fontPlay);
        uiText.setCharacterSize(30);
        uiText.setFillColor(Color(255, 37, 1, 255));

        //Time played
        uiText.setPosition(580, 326);
        uiText.setString(to_string(board.GetTimePlayed()/1000));
        window.draw(uiText);

        //Score
        uiText.setPosition(610, 402);
        uiText.setString(to_string(board.GetPoints()));
        window.draw(uiText);

        window.display();

        if (board.isOver())
            break;
    }

    if (hardMode == "EASY") {
        if (list[list.size() - 1].getPointEASY() < board.GetPoints())
            list[list.size() - 1].setPointEASY(board.GetPoints());
    }
    else if (hardMode == "HARD") {
        if (list[list.size() - 1].getPointHARD() < board.GetPoints())
            list[list.size() - 1].setPointHARD(board.GetPoints());
    }

    //Move to Lose screen
    music_play.stop();
    displayLoseScreen(window, board.GetPoints());
}


// Function to display the Instruction screen
void displayInstructionScreen(RenderWindow& window) {
    // Load and display the "Instruction" screen image
    Texture instructionScreenTexture;
    instructionScreenTexture.loadFromFile("Resources/game_screen/instruction.png");
    Sprite instructionScreen(instructionScreenTexture);
    window.draw(instructionScreen);
    window.display();
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    return;
                }
            }
        }
    }
}

// Function to display the Leaderboard screen
void displayLeaderboardScreen(RenderWindow& window, vector<Player> list, string mode) {
    // Load and display the "Leaderboard" screen image
    Texture leaderboardScreenTexture;
    leaderboardScreenTexture.loadFromFile("Resources/game_screen/leaderboard.png");
    Sprite leaderboardScreen(leaderboardScreenTexture);

    int size = 5;
    // Load font
    Font fontPlay;
    fontPlay.loadFromFile("Resources/font/level-up.otf");

    // NUM
    std::vector<Text> index(size);
    for (int i = 0; i < size; i++) {
        index[i].setFont(fontPlay);
        index[i].setString(to_string(i + 1) + ".");
        index[i].setCharacterSize(30);
        index[i].setFillColor(Color(76, 37, 1, 255));
        index[i].setPosition(70, 350 + i * 50);
    }
    window.clear(Color::Black);

    if (mode == "EASY") {
        sortPlayersEASY(list);
    }
    else if (mode == "HARD") {
        sortPlayersHARD(list);
    }

    // NAME
    std::vector<Text> NamePlayer(size);
    for (int i = 0; i < size; i++) {
        NamePlayer[i].setFont(fontPlay);
        NamePlayer[i].setString(list[i].getName());
        NamePlayer[i].setCharacterSize(30);
        NamePlayer[i].setFillColor(Color(76, 37, 1, 255));
        NamePlayer[i].setPosition(125, 350 + i * 50);
    }
    window.clear(Color::Black);

    // SCORE
    std::vector<Text> ScorePlayer(size);
    for (int i = 0; i < size; i++) {
        ScorePlayer[i].setFont(fontPlay);
        if (mode == "EASY") {
            ScorePlayer[i].setString(to_string(list[i].getPointEASY()));
        }
        else if (mode == "HARD") {
            ScorePlayer[i].setString(to_string(list[i].getPointHARD()));
        }
        ScorePlayer[i].setCharacterSize(30);
        ScorePlayer[i].setFillColor(Color(76, 37, 1, 255));
        ScorePlayer[i].setPosition(550, 350 + i * 50);
    }

    // Draw title screen image    
    window.draw(leaderboardScreen);

    // Draw menu items
    for (int i = 0; i < size; ++i) {
        window.draw(index[i]);
        window.draw(NamePlayer[i]);
        window.draw(ScorePlayer[i]);
    }

    window.display();
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    return;
                }
            }
        }
    }
}

void titleScreen(RenderWindow& window, vector<Player>& list) {
    Texture* titleScreenTexture = new Texture();
    titleScreenTexture->loadFromFile("Resources/game_screen/menu.png");
    Sprite titleScreen(*titleScreenTexture);

    Music music;
    music.openFromFile("Resources/music/intro.wav");
    music.setLoop(true);
    music.setVolume(35.0);
    music.play();

    Music music_move;
    music_move.openFromFile("Resources/music/move.wav");
    music_move.setVolume(35.0);

    Text menuTexts[MENU_ITEM_COUNT];

    Font fontPlay;
    fontPlay.loadFromFile("Resources/font/TypefaceMarioWorldPixelFilledRegular-rgVMx.ttf");

    //Cài đặt cho chữ Play
    menuTexts[0].setFont(fontPlay);
    menuTexts[0].setString(MENU_ITEMS[0]);
    menuTexts[0].setCharacterSize(30);
    menuTexts[0].setFillColor(Color(76, 37, 1, 255));
    menuTexts[0].setPosition(326, 445);

    //Cài đặt cho các chữ còn lại
    Font font;
    font.loadFromFile("Resources/font/PixemonTrialRegular-p7nLK.ttf");
    menuTexts[1].setPosition(310, 537 + 0 * 65);
    menuTexts[2].setPosition(319, 537 + 1 * 65);
    menuTexts[3].setPosition(366, 537 + 2 * 65);

    for (int i = 1; i < MENU_ITEM_COUNT; ++i) {
        menuTexts[i].setFont(font);
        menuTexts[i].setString(MENU_ITEMS[i]);
        menuTexts[i].setCharacterSize(25);
        menuTexts[i].setFillColor(Color(76, 37, 1, 255));
    }

    int selectedItem = 0; // Index of the currently selected menu item

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                writeFile(list);
                window.close();
            }
            else if (event.type == Event::KeyPressed) {
                music_move.play();
                if (event.key.code == Keyboard::Up) {
                    selectedItem = (selectedItem - 1 + MENU_ITEM_COUNT) % MENU_ITEM_COUNT;
                }
                else if (event.key.code == Keyboard::Down) {
                    selectedItem = (selectedItem + 1) % MENU_ITEM_COUNT;
                }
                else if (event.key.code == Keyboard::Enter) {
                    switch (selectedItem) {
                    case 0: //Nút play
                        music.stop();
                        displayPlayScreen(window, displayChooseMode(window), list);
                        music.play();
                        break;
                    case 1: //Nút Leaderboard
                        displayLeaderboardScreen(window, list, displayChooseMode(window));
                        break;
                    case 2: //Nút Instruction
                        displayInstructionScreen(window);
                        break;
                    case 3: //Nút Exit
                        writeFile(list);
                        window.close();
                        break;
                    }
                }
            }
        }

        // Update text color based on selection
        for (int i = 0; i < MENU_ITEM_COUNT; ++i) {
            menuTexts[i].setFillColor(i == selectedItem ? Color::Red : Color(76, 37, 1, 255));
        }

        window.clear(Color::Black);
        window.draw(titleScreen);
        for (int i = 0; i < MENU_ITEM_COUNT; ++i) {
            window.draw(menuTexts[i]);
        }

        window.display();
    }
}