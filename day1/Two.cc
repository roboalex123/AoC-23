#include "../read.h"
#include <vector>
#include <unordered_map>
using namespace std;

int findDigit(string line, const unordered_map<string, int> &digitBank, const int maxChars = 5, const int minChars = 3) {
    for (int i = 0; i < line.size(); i++) { 
        string currentCheck;
        for (int j = 0; j < maxChars; j++) {
            int digit = '0';

            if (isdigit(line[j + i]) and j == 0) {
                return line[j + i] - digit;
            }

            currentCheck += line[j + i];

            if (j + 1 >= minChars and digitBank.count(currentCheck)) {
                return digitBank.at(currentCheck);
            }

        }
    }

    return -1;
} 

int getLineSum(string line, const unordered_map<string, int> &spelledDigits, const unordered_map<string, int> &spelledDigitsReversed) {
    int firstDigit = findDigit(line, spelledDigits);
    if (firstDigit == -1) return 0;

    reverse(line.begin(), line.end());

    int lastDigit = findDigit(line, spelledDigitsReversed);
    if (lastDigit == -1) return 0;

    string result = to_string(firstDigit) + to_string(lastDigit);

    return stoi(result);
}

int main() {
    const unordered_map<string, int> spelledDigits = {
        { "one", 1 },
        { "two", 2 },
        { "three", 3},
        { "four", 4 },
        { "five", 5 },
        { "six", 6 },
        { "seven", 7 },
        { "eight", 8 },
        { "nine", 9 },
        { "zero", 0 }
    };

    const unordered_map<string, int> spelledDigitsReversed = {
        { "eno", 1 },
        { "owt", 2 },
        { "eerht", 3},
        { "ruof", 4 },
        { "evif", 5 },
        { "xis", 6 },
        { "neves", 7 },
        { "thgie", 8 },
        { "enin", 9 },
        { "orez", 0 }
    };

    int sum = 0;

    while (true) {
        string line;

        getline(cin, line); 
        if (!cin) break;

        if (line.empty()) break;

        
        sum += getLineSum(line, spelledDigits, spelledDigitsReversed);
    }

    cout << sum << endl;

    return 0;
}
