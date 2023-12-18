#include "../read.h"
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Card {
    private:
        int id;
        int pointValue;

        unordered_set<int> winningNums;
        vector<int> numbers;

    public:
        // Default constructor
        Card() {
            id = 0;
            pointValue = 0;
        }

        // Getters
        int getId() { return id; }
        int getPointValue() { return pointValue; }

        // Calculate the point value of the card
        void calculatePoints() {
            for (int num : numbers)
                if (winningNums.contains(num))
                    pointValue = pointValue == 0 ? 1 : pointValue * 2;
        }

        // Read a card from a line
        void readCard(string &line) {
            stringstream ss(line);
            string trash = read(ss);

            // Get id
            id = read(ss);

            // Get rid of colon
            char trashChar = read(ss);

            // Get winningNums
            string num = readline(ss, '|');
            stringstream winningNumsStream(num);

            // Insert winningNums into set
            int insertNum;
            while (winningNumsStream >> insertNum) {
                winningNums.insert(insertNum);
            }

            // Get numbers
            string nums = readline(ss);
            stringstream numbersStream(nums);

            // Insert numbers into vector
            while (numbersStream >> insertNum) {
                numbers.push_back(insertNum);
            }

            // Calculate point value
            calculatePoints();
        }

        // Print the card
        void printCard() {
            cout << "Card " << id << ": ";
            for (int num : winningNums) {
                cout << num << " ";
            }
            cout << "| ";
            for (int num : numbers) {
                cout << num << " ";
            }
            cout << endl;
        }
};

int main() {
    string line = readline();

    vector<Card> cards;

    while (cin) {
        Card card;
        card.readCard(line);
        cards.push_back(card);

        line = readline();
    }

    int sum = 0;
    for (Card card : cards) {
        sum += card.getPointValue();
    }

    cout << "The sum of the point values of all cards is " << sum << endl;
}
