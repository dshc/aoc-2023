#include "utils.h"
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

enum Dir { NORTH, SOUTH, EAST, WEST };

using Coord = pair<int, int>;
using Grid = vector<vector<char>>;
using Memo = set<pair<Coord, Dir>>;

map<Dir, Coord> dirToMovement{
    {NORTH, {0, -1}}, {SOUTH, {0, 1}}, {EAST, {1, 0}}, {WEST, {-1, 0}}};

Coord move(const Coord &loc, Dir dir) {
  auto &toAdd = dirToMovement[dir];
  return {loc.first + toAdd.first, loc.second + toAdd.second};
}

void navigate(Memo &memo, set<Coord> &energized, const Grid &grid,
              const Coord &loc, Dir dir) {
  // check if out of bounds
  if (loc.second >= grid.size() || loc.second < 0 ||
      loc.first >= grid[loc.second].size() || loc.first < 0) {
    return;
  }

  if (memo.contains(make_pair(loc, dir)))
    return;

  // add to energized
  energized.emplace(loc);
  memo.emplace(loc, dir);

  // recurse
  auto x = grid[loc.second][loc.first];

  // continue
  if (x == '.') {
    navigate(memo, energized, grid, move(loc, dir), dir);
    return;
  }

  // turn
  if (x == '/') {
    switch (dir) {
    case NORTH:
      navigate(memo, energized, grid, move(loc, EAST), EAST);
      return;
    case SOUTH:
      navigate(memo, energized, grid, move(loc, WEST), WEST);
      return;
    case EAST:
      navigate(memo, energized, grid, move(loc, NORTH), NORTH);
      return;
    case WEST:
      navigate(memo, energized, grid, move(loc, SOUTH), SOUTH);
      return;
    }
  }

  if (x == '\\') {
    switch (dir) {
    case NORTH:
      navigate(memo, energized, grid, move(loc, WEST), WEST);
      return;
    case SOUTH:
      navigate(memo, energized, grid, move(loc, EAST), EAST);
      return;
    case EAST:
      navigate(memo, energized, grid, move(loc, SOUTH), SOUTH);
      return;
    case WEST:
      navigate(memo, energized, grid, move(loc, NORTH), NORTH);
      return;
    }
  }

  // split
  if (x == '|') {
    switch (dir) {
    case NORTH:
    case SOUTH:
      navigate(memo, energized, grid, move(loc, dir), dir);
      return;
    case EAST:
    case WEST:
      navigate(memo, energized, grid, move(loc, NORTH), NORTH);
      navigate(memo, energized, grid, move(loc, SOUTH), SOUTH);
      return;
    }
  }

  if (x == '-') {
    switch (dir) {
    case EAST:
    case WEST:
      navigate(memo, energized, grid, move(loc, dir), dir);
      return;
    case NORTH:
    case SOUTH:
      navigate(memo, energized, grid, move(loc, EAST), EAST);
      navigate(memo, energized, grid, move(loc, WEST), WEST);
      return;
    }
  }
}

void day16() {
  Grid grid = utils::parseIntoVecVec("../inputs/16a.txt");

  Coord start{0, 0};
  Dir dir = EAST;

  Memo memo; // for remembering if we've gone down this path before
  set<Coord> energized;
  navigate(memo, energized, grid, start, dir);

  cout << "part1: " << energized.size() << endl;

  int max = 0;

  // start from top
  for (int x = 0; x < grid[0].size(); ++x) {
    start = make_pair(x, 0);
    memo.clear();
    energized.clear();
    navigate(memo, energized, grid, start, SOUTH);
    if (energized.size() > max)
      max = energized.size();
  }
  // start from bottom
  for (int x = 0; x < grid[0].size(); ++x) {
    start = make_pair(x, grid[0].size() - 1);
    memo.clear();
    energized.clear();
    navigate(memo, energized, grid, start, NORTH);
    if (energized.size() > max)
      max = energized.size();
  }

  // start from left
  for (int x = 0; x < grid.size(); ++x) {
    start = make_pair(0, x);
    memo.clear();
    energized.clear();
    navigate(memo, energized, grid, start, EAST);
    if (energized.size() > max)
      max = energized.size();
  }
  
  // start from right
  for (int x = 0; x < grid.size(); ++x) {
    start = make_pair(grid.size() - 1, x);
    memo.clear();
    energized.clear();
    navigate(memo, energized, grid, start, WEST);
    if (energized.size() > max)
      max = energized.size();
  }

  cout << "part2: " << max << endl;
}
