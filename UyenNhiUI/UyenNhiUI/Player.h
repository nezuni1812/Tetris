#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Player {
private:
    string name;
    int point;
public:
    Player();
    Player(string name, int point);
    string getName();
    int getPoint();
};

/*void writeFile(Player* listPlayer, int n);*/

vector<Player> inputPlayerInfo();