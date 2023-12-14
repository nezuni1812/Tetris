#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <algorithm>
using namespace sf;
using namespace std;

class Player {
private: 
    string name;
    int point;
public:
    Player() : name(""), point(0) {}
    Player(string name, int point) : name(name), point(point) {}
    string getName(){
        return name;
    }
    int getPoint() {
        return point;
    }
};

void writeFile(Player* listPlayer, int n) {
    fstream fs;
    string filename = "Resources/record.txt";
    fs.open(filename, ios::in);
    if (!fs.is_open()) {
        cout << "Can't open file " << filename;
        return;
    }
    fs >> n;
    fs.close();

    fs.open(filename, ios::out);
    if (!fs.is_open()) {
        cout << "Can't open file " << filename;
        return;
    }
    fs << n << endl;

    for (int i = 0; i < n; i++) {
        fs << listPlayer[i].getName() << " ";
        fs << listPlayer[i].getPoint() << " ";
    }
    fs.close();
}
vector<Player> inputPlayerInfo() {
    vector<Player> listPlayer;
    
    fstream fs;
    fs.open("Resources/record.txt");
    if (!fs.is_open()) {
        cout << "Can't open file ";
        return listPlayer;
    }
    int n;
    fs >> n; // Read number of players

    string tempName;
    string tempPoint;
    for (int i = 0; i < n; i++) {
        fs >> tempName;
        fs >> tempPoint;
        listPlayer.push_back(Player(tempName, stoi(tempPoint)));
        //fs.ignore();
    }
    fs.close();
    return listPlayer;
}


const int MENU_ITEM_COUNT = 4;
const string MENU_ITEMS[MENU_ITEM_COUNT] = { "PLAY", "Leaderboard", "Instruction", "Exit" };

// Function to display the Play screen
void displayPlayScreen(sf::RenderWindow& window) {
    // Load and display the "Play" screen image

    sf::Texture playScreenTexture;
    playScreenTexture.loadFromFile("Resources/game_screen.png");
    sf::Sprite playScreen(playScreenTexture);
    window.draw(playScreen);
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
        index[i].setString(to_string(i+1) + ".");
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

int main()
{
    //Music music;
    //music.openFromFile("Resources/intro.wav");

    RenderWindow window(VideoMode(750, 850), "Tetris", Style::Titlebar | Style::Close);
    titleScreen(window);
}