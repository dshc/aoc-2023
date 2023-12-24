#include "utils.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <set>

using namespace std;

using Coord = pair<int, int>;

struct Instruction {
    char dir;
    int length;
    string color;

    Instruction(char d, int l, string c) : dir{d}, length{l}, color{std::move(c)} {}
};

const map<char, Coord> Move {
    {'D', {0, 1}},
    {'U', {0, -1}},
    {'L', {-1, 0}},
    {'R', {1, 0}}
};

void day18() {
    vector<Instruction> instructions;
    std::ifstream ff("../inputs/18a.txt");
    for (string l; getline(ff, l);) {
        auto x = utils::split(l, ' ');
        instructions.emplace_back(x[0][0], std::stoi(x[1]), x[2]);
    }

    // go through instructions starting at (0,0) and track all trenches. Keep track of x-min-max & y-min-max for offsets
    set<Coord> trenches;
    int xmin = 0, xmax = 0, ymin = 0, ymax = 0;
    Coord currCoord = make_pair(0, 0);
    trenches.emplace(currCoord.first, currCoord.second);
    for (auto& i : instructions) {
        const auto& toMove = Move.at(i.dir);
        for (int x = 0; x < i.length; ++x) {
            currCoord.first += toMove.first;
            currCoord.second += toMove.second;
            trenches.emplace(currCoord.first, currCoord.second);
            if (currCoord.first < xmin) xmin = currCoord.first;
            if (currCoord.first > xmax) xmax = currCoord.first;
            if (currCoord.second < ymin) ymin = currCoord.second;
            if (currCoord.second > ymax) ymax = currCoord.second;
        }
    }

    cout << xmin << " " << xmax << " " << ymin << " " << ymax << endl;

    int sum = 0;
    for (int y = ymin; y <= ymax; ++y) {
        bool include = false;
        for (int x = xmin; x <= xmax; ++x) {
            if (trenches.contains({x,y})) {
                ++sum;
                while (trenches.contains({++x,y})) ++sum;
                include = !include;
            } else if (include) {
                ++sum;
            } else {
                cout << x << " : " << y << endl;
            }
        }
    }

    cout << "part1: " << sum << endl;
}
