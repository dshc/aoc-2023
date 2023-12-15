#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const pair<int, int> turnSouth = make_pair(0, 1);
const pair<int, int> turnNorth = make_pair(0, -1);
const pair<int, int> turnWest = make_pair(-1, 0);
const pair<int, int> turnEast = make_pair(1, 0);

pair<int, int> getNewDir(pair<int, int> currDir, char c) {
  if (c == '|' || c == '-')
    return currDir; // continue along the same route

  if (c == '7') {
    if (currDir.first == 1) {
      return turnSouth;
    } else {
      return turnWest;
    }
  }

  if (c == 'F') {
    if (currDir.first == 0) {
      return turnEast;
    } else {
      return turnSouth;
    }
  }

  if (c == 'L') {
    if (currDir.first == 0) {
      return turnEast;
    } else {
      return turnNorth;
    }
  }

  if (c == 'J') {
    if (currDir.first == 0) {
      return turnWest;
    } else {
      return turnNorth;
    }
  }

  return currDir;
}

void day10part1() {
  int result = 0;

  pair<int, int> dir = make_pair(-1, 0);
  vector<vector<char>> map;
  pair<int, int> currLocation; // x, y coord
  int x = 0, y = 0;

  ifstream f("../inputs/10a.txt");
  for (string l; getline(f, l);) {
    auto &row = map.emplace_back();
    for (auto &c : l) {
      if (c == 'S')
        currLocation = make_pair(x, y);
      row.emplace_back(c);
      ++x;
    }
    x = 0;
    ++y;
  }

  // create a new map with only the loop
  vector<vector<char>> newmap(map.size(), vector<char>(map[0].size(), '.'));
  int borderLength = 0;
  do {
    newmap[currLocation.second][currLocation.first] =
        map[currLocation.second][currLocation.first];

    // move along
    ++borderLength;
    currLocation.first += dir.first;
    currLocation.second += dir.second;

    // update direction
    dir = getNewDir(dir, map[currLocation.second][currLocation.first]);
  } while (map[currLocation.second][currLocation.first] != 'S');

  cout << "part1: " << borderLength / 2 << endl;

  // i cheated and looked up how other people tackled this
  // This uses the idea that as you scan left to right, if youve crossed an odd
  // number of vertical walls, then you are inside the loop.
  int part2sum = 0;
  for (int y = 0; y < newmap.size(); ++y) {
    bool insideLoop = false;
    for (int x = 0; x < newmap[y].size(); ++x) {
      char a = newmap[y][x];
      if (a == '|' || a == 'J' || a == 'L' || a == 'S') {
        insideLoop = !insideLoop;
      } else {
        if (insideLoop && a == '.') {
          ++part2sum;
        }
      }
    }
  }
  cout << "part2: " << part2sum << endl;
}
