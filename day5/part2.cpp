#include<iostream>
#include<stdlib.h>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<sstream>
#include<limits.h>

using namespace std;
unordered_map<long long, vector<long long>> seed_to_soil_map;
unordered_map<long long, vector<long long>> soil_to_fertilizer_map;
unordered_map<long long, vector<long long>> fertilizer_to_water_map;
unordered_map<long long, vector<long long>> water_to_light_map;
unordered_map<long long, vector<long long>> light_to_temp_map;
unordered_map<long long, vector<long long>> temp_to_humidity_map;
unordered_map<long long, vector<long long>> humidity_to_location_map;

void mapping(unordered_map<long long, vector<long long>>& mp, string& temp) {
    while (getline(cin, temp)) {
        if (temp.empty()) {
            break;
        }
        // cout << temp << endl;
        istringstream ss(temp);
        string token;
        long long to = -1;
        long long from = -1;
        long long range = -1;
        while (ss >> token) {
            if (token == " ") continue;
            if (to == -1) {
                to = stoll(token);
            }
            else if (from == -1) {
                from = stoll(token);
            }
            else {
                range = stoll(token);
            }
        }
        mp[to].push_back(from);
        mp[to].push_back(from + range);
    }
}

long long value(unordered_map<long long, vector<long long>>& mp, long long key) {
    for (auto it = mp.begin(); it != mp.end(); it++) {
        for (int i = 0; i < it->second.size(); i+=2) {
            if (it->second[i] <= key && key < it->second[i+1]) {
                return it->first + key - it->second[i];
            }
        }
    }
    return key;
}

long long solve(long long seed) {
    long long soil = value(seed_to_soil_map, seed);
    long long fertilizer = value(soil_to_fertilizer_map, soil);
    long long water = value(fertilizer_to_water_map, fertilizer);
    long long light = value(water_to_light_map, water);
    long long temp = value(light_to_temp_map, light);
    long long humidity = value(temp_to_humidity_map, temp);
    long long location = value(humidity_to_location_map, humidity);
    // cout << seed << " " << soil << " " << fertilizer << " " << water << " " << light << " " << temp << " " << humidity << " " << location << endl;
    return location;
}

int main() {
    string line;
    long long ans = LONG_LONG_MAX;

    string seeds;
    getline(cin, seeds);
    istringstream ss(seeds.substr(6));
    vector<long long> seed_vec;
    string token;
    while (ss >> token) {
        if (token == " ") continue;
        seed_vec.push_back(stoll(token));
    }

    while (getline(cin, line)) {
        string temp;
        if (line == "seed-to-soil map:") {
            mapping(seed_to_soil_map, temp);
        }
        else if (line == "soil-to-fertilizer map:") {
            mapping(soil_to_fertilizer_map, temp);
        }
        else if (line == "fertilizer-to-water map:") {
            mapping(fertilizer_to_water_map, temp);
        }
        else if (line == "water-to-light map:") {
            mapping(water_to_light_map, temp);
        }
        else if (line == "light-to-temperature map:") {
            mapping(light_to_temp_map, temp);
        }
        else if (line == "temperature-to-humidity map:") {
            mapping(temp_to_humidity_map, temp);
        }
        else if (line == "humidity-to-location map:") {
            mapping(humidity_to_location_map, temp);
        }
    }

    for (int i = 0; i < seed_vec.size(); i+=2) {
        long long seed = seed_vec[i];
        long long upperSeed = seed_vec[i] + seed_vec[i+1];
        long long loc = solve(seed);
        long long upperLoc = solve(upperSeed);
        ans = min(ans, loc);
        ans = min(ans, upperLoc);
        while (seed <= upperSeed) {
            long long mid = seed + (upperSeed - seed) / 2;
            long long midLoc = solve(mid);
            if (midLoc < loc && midLoc < upperLoc) {
                upperSeed = mid - 1;
                upperLoc = midLoc;
                ans = min(ans, midLoc);
            }
            else {
                // perform normal binary search
                if (midLoc < loc) {
                    upperSeed = mid - 1;
                    upperLoc = midLoc;
                    ans = min(ans, midLoc);
                }
                else {
                    seed = mid + 1;
                    loc = midLoc;
                    ans = min(ans, midLoc);
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}