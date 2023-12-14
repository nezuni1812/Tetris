#include "Player.h"

Player::Player() : name(""), point(0) {}
Player::Player(string name, int point) : name(name), point(point) {}
string Player::getName() {
    return name;
}
int Player::getPoint() {
    return point;
}


/*void writeFile(Player* listPlayer, int n) {
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
}*/

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
