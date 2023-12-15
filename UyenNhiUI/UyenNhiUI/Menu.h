#pragma once
#include <iostream>
#include "Player.h"
#include <SFML/Graphics.hpp> //Class Texture, Sprite, Text, Color
#include <SFML/Window.hpp> //Class RenderWindow, Event, Keyboard, 
#include <SFML/Audio.hpp> //Class Music
#include <vector>
#include <string>

using namespace sf;
using namespace std;

const int MENU_ITEM_COUNT = 4;
const string MENU_ITEMS[MENU_ITEM_COUNT] = { "PLAY", "Leaderboard", "Instruction", "Exit" };

const int MODE_COUNT = 2;
const string MODE_CHOOSE[MODE_COUNT] = { "EASY", "HARD" };

void displayLoginScreen(sf::RenderWindow& window, vector<Player>& list);
void displayLoseScreen(sf::RenderWindow& window, int score);
string displayChooseMode(RenderWindow& window);
void displayPlayScreen(sf::RenderWindow& window, string mode);
void displayInstructionScreen(sf::RenderWindow& window);
void displayLeaderboardScreen(sf::RenderWindow& window, vector<Player> list, string mode);

void titleScreen(sf::RenderWindow& window, vector<Player>& list);