#include "utils.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <set>

using namespace std;

using ll = long long;
using Coord = pair<ll, ll>;

struct Instruction {
    char dir;
    ll length;
    string color;

    Instruction(char d, int l, string c) : dir{d}, length{l}, color{std::move(c)} {}
};

const map<char, Coord> Move {
    {'D', {0, 1}},
    {'U', {0, -1}},
    {'L', {-1, 0}},
    {'R', {1, 0}}
};

const map<char, char> NewDir {
    {'0', 'R'},
    {'1', 'D'},
    {'2', 'L'},
    {'3', 'U'},
};

void day18() {
    vector<Instruction> instructions;
    std::ifstream ff("../inputs/18a.txt");
    for (string l; getline(ff, l);) {
        auto x = utils::split(l, ' ');
        instructions.emplace_back(x[0][0], std::stoi(x[1]), x[2]);
    }

    {
        // go through instructions starting at (0,0) and track all trenches. Keep track of x-min-max & y-min-max for offsets
        set<Coord> trenches;
        set<Coord> walls;
        char prevDir = 'S';
        int xmin = 0, xmax = 0, ymin = 0, ymax = 0;
        Coord currCoord = make_pair(0, 0);
        trenches.emplace(currCoord.first, currCoord.second);
        walls.emplace(currCoord.first, currCoord.second);
        for (auto& i : instructions) {
            const auto& toMove = Move.at(i.dir);
            for (int x = 0; x < i.length; ++x) {
                if (i.dir == 'D' || prevDir == 'U')
                    walls.emplace(currCoord.first, currCoord.second);
                currCoord.first += toMove.first;
                currCoord.second += toMove.second;
                if (currCoord.first < xmin) xmin = currCoord.first;
                if (currCoord.first > xmax) xmax = currCoord.first;
                if (currCoord.second < ymin) ymin = currCoord.second;
                if (currCoord.second > ymax) ymax = currCoord.second;
                trenches.emplace(currCoord.first, currCoord.second);
                prevDir = i.dir;
            }
        }

        int sum = 0;
        for (int y = ymin; y <= ymax; ++y) {
            bool include = false;
            for (int x = xmin; x <= xmax; ++x) {
                if (walls.contains({x,y})) include = !include;
                if (trenches.contains({x,y}) || include) ++sum;
            }
        }

        cout << "part1: " << sum << endl;
    }

    {
        vector<Instruction> newInstructions;
        newInstructions.reserve(instructions.size());
        for (auto& i : instructions) {
            char * p;
            long dist = std::strtoul(i.color.substr(2, 5).c_str(), &p, 16);
            string direction = i.color.substr(7, 1);
            newInstructions.emplace_back(NewDir.at(direction[0]), dist, "");
        }

        // find points
        ll borderLength = 0;
        Coord currCoord = make_pair(0, 0);
        vector<Coord> points;
        points.emplace_back(currCoord.first, currCoord.second);
        for (auto& i : newInstructions) {
            const auto& toMove = Move.at(i.dir);
            borderLength += i.length;
            if (i.dir == 'R') currCoord.first += i.length;
            else if (i.dir == 'L') currCoord.first -= i.length;
            else if (i.dir == 'U') currCoord.second -= i.length;
            else if (i.dir == 'D') currCoord.second += i.length;
            points.emplace_back(currCoord.first, currCoord.second);
        }

        // shoelace formula
        ll area = 0;
        for (int i = 0; i < points.size() - 1; ++i) {
            auto& a = points[i];
            auto& b = points[i+1];
            area += ((a.first*b.second) - (a.second*b.first));
        }

        area = area / 2;
        ll sum = (area + 1 - (borderLength / 2)) + borderLength;
        cout << "part2: " << sum << endl;
    }
}
