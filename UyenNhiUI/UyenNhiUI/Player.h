#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

class Player {
private:
    string name;
    int pointEASY;
    int pointHARD;
public:
    Player();
    Player(string name, int pointEASY, int pointHARD);
    string getName();
    int getPointEASY();
    int getPointHARD();
    static bool compareByPointEASY(const Player& a, const Player& b);
    static bool compareByPointHARD(const Player& a, const Player& b);
};

//void writeFile(vector<Player> listPlayer);
vector<Player> inputPlayerInfo();
void sortPlayersEASY(std::vector<Player>& list);
void sortPlayersHARD(std::vector<Player>& list);