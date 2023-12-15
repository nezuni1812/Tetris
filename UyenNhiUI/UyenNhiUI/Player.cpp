#include "Player.h"

Player::Player() : name(""), pointEASY(0), pointHARD(0) {}
Player::Player(string name, int pointEASY, int pointHARD) : name(name), pointEASY(pointEASY), pointHARD(pointHARD){}
string Player::getName() {
    return name;
}
int Player::getPointEASY() {
    return pointEASY;
}
int Player::getPointHARD() {
    return pointHARD;
}

bool Player::compareByPointEASY(const Player& a, const Player& b) {
    return a.pointEASY > b.pointEASY;
}

bool Player::compareByPointHARD(const Player& a, const Player& b) {
    return a.pointHARD > b.pointHARD;
}

/*void writeFile(vector<Player> listPlayer) {
    fstream fs;
    string filename = "Resources/record.txt";
    fs.open(filename, ios::out);
    if (!fs.is_open()) {
        cout << "Can't open file " << filename;
        return;
    }

    fs << listPlayer.size() << endl;

    for (int i = 0; i < listPlayer.size(); i++) {
        fs << listPlayer[i].getName() << " ";
        fs << listPlayer[i].getPointEASY() << " ";
        fs << listPlayer[i].getPointHARD() << " ";
        fs << "\n";
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
    fs >> n; 

    string tempName;
    string tempPointEASY, tempPointHARD;
    for (int i = 0; i < n; i++) {
        fs >> tempName;
        fs >> tempPointEASY;
        fs >> tempPointHARD;
        listPlayer.push_back(Player(tempName, stoi(tempPointEASY), stoi(tempPointHARD)));
    }
    fs.close();
    return listPlayer;
}

void sortPlayersEASY(vector<Player>& list) {
    sort(list.begin(), list.end(), Player::compareByPointEASY);
}
void sortPlayersHARD(vector<Player>& list) {
    sort(list.begin(), list.end(), Player::compareByPointHARD);
}