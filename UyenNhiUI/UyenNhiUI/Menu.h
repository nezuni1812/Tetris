#pragma once
#include <iostream>
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

using namespace sf;
using namespace std;

const int MENU_ITEM_COUNT = 4;
const string MENU_ITEMS[MENU_ITEM_COUNT] = { "PLAY", "Leaderboard", "Instruction", "Exit" };

void displayPlayScreen(sf::RenderWindow& window);
void displayInstructionScreen(sf::RenderWindow& window);
void displayLeaderboardScreen(sf::RenderWindow& window, vector<Player> list);

void titleScreen(RenderWindow& window);