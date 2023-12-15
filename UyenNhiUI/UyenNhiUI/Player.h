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
    void setPointEASY(int pointEASY);
    void setPointHARD(int pointHARD);
    friend bool compareByPointEASY(const Player& a, const Player& b);
    friend bool compareByPointHARD(const Player& a, const Player& b);
};

void writeFile(vector<Player> listPlayer);
vector<Player> inputPlayerInfo();
void sortPlayersEASY(std::vector<Player>& list);
void sortPlayersHARD(std::vector<Player>& list);