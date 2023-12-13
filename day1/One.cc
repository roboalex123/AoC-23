#include "../read.h"
#include <vector>
using namespace std;

int getLineSum(string line) {
    vector<int> digits;

    for (int i = 0; i < line.size(); i++) {
        if (!isdigit(line[i])) continue;

        int digit = line[i] - '0';
        digits.push_back(digit);
    }

    string result = to_string(digits[0]) + to_string(digits.back());

    return stoi(result);
}

int main() {
    int sum = 0;

    while (true) {
        string line;

        getline(cin, line); 
        if (!cin) break;

        if (line.empty()) break;

        sum += getLineSum(line);
    }

    cout << sum << endl;

    return 0;
}
