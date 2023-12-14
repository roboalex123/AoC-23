#include "../read.h"
#include <sstream>
#include <vector>
using namespace std;

class Game {
    private:
        int id;

        int maxRedSeen;
        int maxGreenSeen;
        int maxBlueSeen;

    public:
        Game() {
            id = 0;
            maxRedSeen = 0;
            maxGreenSeen = 0;
            maxBlueSeen = 0;
        }

        Game(int id, int maxRedSeen, int maxGreenSeen, int maxBlueSeen) {
            this->id = id;
            this->maxRedSeen = maxRedSeen;
            this->maxGreenSeen = maxGreenSeen;
            this->maxBlueSeen = maxBlueSeen;
        }

        //Getters
        int getId() { return id; }
        
        //Methods
        void insertRed(int red) { if (red > maxRedSeen) { maxRedSeen = red; } }

        void insertGreen(int green) { if (green > maxGreenSeen) { maxGreenSeen = green; } }

        void insertBlue(int blue) { if (blue > maxBlueSeen) { maxBlueSeen = blue; } }

        void readGame(string line) {
            stringstream sts(line);

            string temp = read(sts);

            id = read(sts);

            char colon = read(sts);

            string turn = readline(sts, ';');
            while (sts) {
                stringstream turnStream(turn);

                string pull = readline(turnStream, ',');
                while (turnStream) {
                    stringstream pullStream(pull);

                    int number = read(pullStream);
                    string color = read(pullStream);

                    if (color == "red") {
                        insertRed(number);
                    } else if (color == "green") {
                        insertGreen(number);
                    } else if (color == "blue") {
                        insertBlue(number);
                    }

                    pull = readline(turnStream, ',');
                }

                turn = readline(sts, ';');
            }
        }

        int getPower() {
            return maxRedSeen * maxGreenSeen * maxBlueSeen;
        }


        //Operators
        bool operator<=(const Game& other) const {
            return (maxRedSeen <= other.maxRedSeen) and (maxGreenSeen <= other.maxGreenSeen) and (maxBlueSeen <= other.maxBlueSeen);
        }
};

int main() {
    string line = readline();

    vector<Game> games;

    while (cin) {
        Game game;
        game.readGame(line);

        games.push_back(game); 

        line = readline();
    }

    //Sum the ids of the valid games
    int sum = 0;
    for (int i = 0; i < games.size(); i++) {
        sum += games[i].getPower();
    }

    cout << "Sum of the games' power: " << sum << endl;
}
