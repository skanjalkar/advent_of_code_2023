#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    string line;
    int red, green, blue;
    red = 12;
    green = 13;
    blue = 14;
    long long sum = 0;

    while (getline(cin, line)) {
        size_t idPos = line.find(":");
        string game = line.substr(0, idPos);
        string information = line.substr(idPos + 1);

        information.erase(remove(information.begin(), information.end(), ' '), information.end());
        // cout << information << endl;
        // cout << endl;
        string token;
        istringstream iss(information);
        vector<string> tokens;

        int tempRed = 0;
        int tempGreen = 0;
        int tempBlue = 0;

        while (getline(iss, token, ';')) {
            tokens.push_back(token);
        }

        int id = stoi(game.substr(5, game.length() - 5));

        for (auto i : tokens) {
            vector<string> gameInfo;
            istringstream iss2(i);
            while (getline(iss2, token, ',')) {
                gameInfo.push_back(token);
            }
            for (auto j : gameInfo) {
                // cout << j << endl;
                if (j[j.size()-1] == 'e') {
                    size_t post = j.find('b');
                    tempBlue = max(stoi(j.substr(0, post)), tempBlue);
                }
                else if (j[j.size()-1] == 'n') {
                    size_t post = j.find('g');
                    tempGreen = max(stoi(j.substr(0, post)), tempGreen);
                }
                else if (j[j.size()-1] == 'd') {
                    size_t post = j.find('r');
                    tempRed = max(stoi(j.substr(0, post)), tempRed);
                }
            }
        }
        sum += tempBlue * tempGreen * tempRed;
    }
    cout << sum << endl;

    return 0;
}