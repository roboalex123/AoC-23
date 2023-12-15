#include "../read.h"
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
using namespace std;

class Card {
    private:
        int id;
        int numMatches;

        unordered_set<int> winningNums;
        vector<int> numbers;

    public:
        // Default constructor
        Card() {
            id = 0;
            numMatches = 0;
        }

        // Getters
        int getId() { return id; }
        int getPointValue() { return numMatches; }

        // Calculate the point value of the card
        void calculatePoints() {
            for (int num : numbers)
                if (winningNums.contains(num))
                    numMatches++;
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
    vector<int> numCards;

    while (cin) {
        Card card;
        card.readCard(line);
        cards.push_back(card);
        numCards.push_back(1);

        line = readline();
    }


    for (int i = 0; i < cards.size(); i++) {
        int currId = cards[i].getId();
        for (int k = 0; k < numCards[i]; k++) {
            for (
                    int j = (currId + 1);
                    j <= (currId + cards[i].getPointValue());
                    j++
                ) {
                numCards[j - 1]++;
            }
        }
    }

    int sum = accumulate(numCards.begin(), numCards.end(), 0);

    cout << "The total # of cards: " << sum << endl;

    return 0;
}
