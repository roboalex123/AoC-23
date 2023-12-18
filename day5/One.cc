#include "../read.h"
#include <vector>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <climits>
using namespace std;

struct Range {
    int min;
    int max;

    Range(int min, int rangeLength) {
        this->min = min;
        this->max = min + rangeLength;
    }

    bool inRange(int value) {
        return value >= min and value <= max;
    }
};

struct stringPair {
    string one;
    string two;

    stringPair(string one, string two) {
        this->one = one;
        this->two = two;
    }

    bool operator==(const stringPair &other) const {
        return one == other.one and two == other.two;
    }

};

namespace std {
    template <>
    struct hash<stringPair> {
        size_t operator()(const stringPair &pair) const {
            return hash<string>()(pair.one) ^ hash<string>()(pair.two);
        }
    };
}

class Conversion {
    private:
        string conversionName;

        string sourceUnit;
        vector<Range> sourceRanges;

        string destinationUnit;
        vector<Range> destinationRanges;

        vector<int> conversionRates;

    public:
        Conversion() {}

        // Getters
        string getSourceUnit() {
            return sourceUnit;
        }

        string getDestinationUnit() {
            return destinationUnit;
        }

        void readRanges(string &line) {
            stringstream ss(line);

            int destinationMin = read(ss);
            int sourceMin = read(ss);
            int rangeLength = read(ss);

            sourceRanges.push_back(Range(sourceMin, rangeLength));

            destinationRanges.push_back(Range(destinationMin, rangeLength));

            conversionRates.push_back(destinationMin - sourceMin);
        }

        // Read just the sourceUnit and destinationUnit
        // Format: "sourceUnit-to-destinationUnit map:"
        void readUnits(string &line) {
            stringstream ss(line);

            ss >> conversionName;

            stringstream ss2(conversionName);

            // Read source unit
            sourceUnit = readline(ss2, '-');

            // Read destination unit
            destinationUnit =  readline(ss2);
            // Remove -to- from destinationUnit
            destinationUnit = destinationUnit.substr(3);
        }

        void readConversion(vector<string> &lines) {
            // Read sourceUnit and destinationUnit
            readUnits(lines.at(0));

            // Read ranges
            for (int i = 1; i < lines.size(); i++) {
                readRanges(lines[i]);
            }
        }

        int findConversionRate(int input, bool isSource) {
            vector<Range> ranges = isSource ? sourceRanges : destinationRanges;
            for (int i = 0; i < ranges.size(); i++) {
                if (ranges[i].inRange(input)) {
                    return conversionRates[i];
                }
            }

            return 0;
        }

        int convert(string &inputType, string &outputType, int input) {
            if (inputType == sourceUnit and outputType == destinationUnit) {
                int conversionRate = findConversionRate(input, true);
                //cout << "Conversion rate: " << conversionRate << endl;
                return input + conversionRate;
            } else {
                return 0;
            }
        }
};

class Conversions {
    private:
        unordered_map<stringPair, Conversion> conversionsBank;

        unordered_map<string, string> sourceToDestination;

    public:
        Conversions() {}

        void readConversions(vector<vector<string>> &lines) {
            for (int i = 0; i < lines.size(); i++) {

                if (lines[i].size() == 0) { continue; }

                Conversion conversion;
                conversion.readConversion(lines[i]);

                conversionsBank[stringPair(conversion.getSourceUnit(), conversion.getDestinationUnit())] = conversion;

                sourceToDestination[conversion.getSourceUnit()] = conversion.getDestinationUnit();
            }
        }

        int convert(string &inputType, string &outputType, int input) {
            string sourceUnit = inputType;
            //cout << "Source unit: " << sourceUnit << endl;
            string destinationUnit = outputType;
            //cout << "Destination unit: " << destinationUnit << endl;
            int output = input;

            bool conversionFound = false;

            if (sourceUnit == destinationUnit) {
                return input;
            }

            while (true) {
                //cout << endl;
                //cout << "Conversuion: " << endl;
                if (!sourceToDestination.contains(sourceUnit)) {
                    //cout << "Conversion not found" << endl;
                    break;
                }

                destinationUnit = sourceToDestination[sourceUnit];
                //cout << "Destination unit: " << destinationUnit << endl;

                if (destinationUnit == outputType) { conversionFound = true; }

                output = conversionsBank[stringPair(sourceUnit, destinationUnit)].convert(sourceUnit, destinationUnit, output);
                //cout << "Output: " << output << endl;

                if (conversionFound) { return output; }

                sourceUnit = destinationUnit;
                //cout << "Source unit: " << sourceUnit << endl;
            }
        }
};

int main() {
    Conversions conversionsList;

    vector<int> startingValues;

    string topLine = readline(cin, ' ');
    topLine = readline();

    stringstream ss(topLine);
    int value;
    while (ss >> value) {
        startingValues.push_back(value);
    }

    // print starting values
    cout << "Top line: " << topLine << endl;

    for (int i = 0; i < startingValues.size(); i++) {
        cout << startingValues[i] << " ";
    }
    cout << endl;

    
    string line;
    cout << "Line: " << line << endl;

    vector<vector<string>> lines;


    vector<string> conversion;
    while (getline(cin, line)) {
        cout << "Here" << endl;
        if (line == "") {
            lines.push_back(conversion);
            for (int i = 0; i < conversion.size(); i++) {
                cout << conversion.at(i) << endl;
            }
            conversion.clear();
        } else {
            conversion.push_back(line);
        }
    }


    cout << "Conversion: " << endl;
    for (int i = 0; i < conversion.size(); i++) {
        cout << conversion.at(i) << endl;
        cout << "Here" << endl;
    }


    lines.push_back(conversion);
    cout << "Here" << endl;

    conversionsList.readConversions(lines);
    cout << "Here 2" << endl;

    vector<int> convertedValues;

    string inputType = "seed";
    string outputType = "location";

    cout << "Number of starting values: " << endl;
    cout << startingValues.size() << endl << endl;

    // Convert starting values
    for (int i = 0; i < startingValues.size(); i++) {
        cout << "Here 6" << endl;
        convertedValues.push_back(conversionsList.convert(inputType, outputType, startingValues[i]));
        cout << "Here 5" << endl;
    }

    cout << "Here 3" << endl;
    int minLocation = convertedValues[0];
    cout << "Here 4" << endl;

    // print converted values
    for (int i = 0; i < convertedValues.size(); i++) {
        // original value -> converted value; 
        cout << startingValues[i] << " -> " << convertedValues[i] << endl;
        if (convertedValues[i] < minLocation) {
            minLocation = convertedValues[i];
        }
    }

    cout << "Min location: " << minLocation << endl;


    return 0;
}
