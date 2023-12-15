#include "../read.h"
#include <vector>
#include <cctype>
#include <unordered_map>
using namespace std;

struct Point {
    int y, x;

    bool operator==(const Point &other) const {
        return y == other.y and x == other.x;
    }
};

namespace std {
    template <>
    struct hash<Point> {
        size_t operator()(const Point &p) const {
            return hash<int>()(p.y) ^ (hash<int>()(p.x) << 1);
        }
    };
}

unordered_map<Point, int> seen; 

class Map {
    private:
        vector<vector<char>> map;

        Point size;

        void calculateSize() { size = {map.size(), map[0].size()}; }


    public:
        // Constructors
        Map() {
            size = {0, 0};
        }

        Map(vector<vector<char>> map) {
            this->map = map;
            calculateSize();
        }

        // Setters
        void appendRow(const vector<char> &row) {
            map.push_back(row);
            calculateSize();
        }

        void appendCol(const vector<char> &col) {
            for (int i = 0; i < col.size(); i++) {
                map[i].push_back(col[i]);
            }
            calculateSize();
        }

        // Getters
        Point getSize() const { return size; }

        int getSize(char axis) const {
            if (tolower(axis) == 'x') { return size.x; }
            else if (tolower(axis) == 'y') { return size.y; }
            else { return size.x; }
        }

        char at(const Point &pos) const {
            return map.at(pos.y).at(pos.x);
        }

        int checkNumber(const Point &pos, const string &number) const {
            Point start = {
                (pos.y - 1 < 0 ? 0 : pos.y - 1)
                    ,
                (((pos.x - int(number.size() + 1)) < 0) ?  0 : pos.x - (number.size() + 1))
            };

            Point end = {
                (pos.y + 1 >= getSize('y') ? getSize('y') - 1 : pos.y + 1)
                    ,
                pos.x
            };


            for (int i = start.y; i <= end.y; i++) 
                for (int j = start.x; j <= end.x; j++)
                    if (at({i, j}) == '*') {
                        if (seen.contains({i, j})) {
                            seen.at({i, j}) *= stoi(number);
                            return seen.at({i, j});
                        }
                        seen.insert({{i, j}, stoi(number)});
                        return 0;
                    }

            return 0;

        }
};


int main() {
    Map map;

    string line = readline();

    // Read map
    while (cin) {
        map.appendRow(vector<char>(line.begin(), line.end()));

        line = readline();
    }

    map.appendCol(vector<char>(map.getSize('y'), '.'));

    int sum = 0;
    string currNumber = "";
    for (int i = 0; i < map.getSize('y'); i++) {
        currNumber = "";
        for (int j = 0; j < map.getSize('x'); j++) {
            Point currPos = {i, j};

            if (isdigit(map.at(currPos))) {
                currNumber += map.at(currPos);
            } else if ((map.at(currPos) == '.' or map.at(currPos) == '*') and currNumber != "") {
                sum += map.checkNumber(currPos, currNumber);
                
                currNumber = "";
            }
        }
    }

    cout << sum << endl;
}
