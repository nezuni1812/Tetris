#include <iostream>
#include <fstream>

class Player {
public:
    std::string username;
    int score;
    int time; //seconds
};

class GameData {
private:
    std::string filename;

public:
    GameData(const std::string& file) : filename(file) {}

    void writeFile(Player* listPlayer, int n) {
        std::fstream fs;
        fs.open(filename, std::ios::in);
        if (!fs.is_open()) {
            std::cout << "Can't open file " << filename;
            return;
        }

        fs >> n;

        fs.close();

        fs.open(filename, std::ios::out);
        if (!fs.is_open()) {
            std::cout << "Can't open file " << filename;
            return;
        }

        fs << n << std::endl;

        for (int i = 0; i < n; i++) {
            fs << listPlayer[i].username << " ";
            fs << listPlayer[i].score << " ";
            fs << listPlayer[i].time << " " << std::endl;
        }

        fs.close();
    }

    Player* inputPlayerInfo(int& n) {
        Player* listPlayer = NULL;

        std::fstream fs;
        fs.open(filename);
        if (!fs.is_open()) {
            std::cout << "Can't open file " << filename;
            return NULL;
        }

        fs >> n; // Read number of players

        listPlayer = new Player[n];

        for (int i = 0; i < n; i++) {
            fs >> listPlayer[i].username;
            fs >> listPlayer[i].score;
            fs >> listPlayer[i].time;

            fs.ignore();
        }

        fs.close();

        return listPlayer;
    }

    void leaderboard(Player* listPlayer, int n) {
        std::fstream fs;
        fs.open(filename, std::ios::in);
        if (!fs.is_open()) {
            std::cout << "Can't open file " << filename;
            return;
        }

        fs >> n;
        fs.close();

        Player* rank = new Player[n];

        // Arrange rank
        for (int i = 0; i < n; i++)
            rank[i] = listPlayer[i];

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                // Compare based on score and time played
                if (rank[j].score < rank[j + 1].score ||
                    (rank[j].score == rank[j + 1].score && rank[j].time > rank[j + 1].time)) {
                    // Swap
                    Player temp = rank[j];
                    rank[j] = rank[j + 1];
                    rank[j + 1] = temp;
                }
            }
        }

        // Display the arranged leaderboard
        std::cout << "Leaderboard\n";
        for (int i = 0; i < n; i++) {
            std::cout << (i + 1) << ". " << rank[i].username << " - Score: " << rank[i].score << ", Time: " << rank[i].time << " secs\n";
        }

        delete[] rank;
    }
};

int main() {
    GameData game("records.txt");

    int numPlayers = 0;
    Player* players = game.inputPlayerInfo(numPlayers);

    if (players != NULL) {
        game.leaderboard(players, numPlayers);
        delete[] players;
    } else {
        std::cout << "No player data available." << std::endl;
    }

    return 0;
}
