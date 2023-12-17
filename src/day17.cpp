#include "utils.h"
#include <iostream>
#include <map>
#include <queue>
#include <set>

using namespace std;

using Coord = pair<int, int>;

namespace {
enum Dir { NORTH, SOUTH, EAST, WEST };

struct Node {
  Coord coord;
  int cost;
  Dir dir;
  int stepCount;

  Node(Coord c, int co, Dir d, int sc)
      : coord(c), cost(co), dir(d), stepCount(sc) {}
};

map<Dir, Coord> dirToMovement{
    {NORTH, {0, -1}}, {SOUTH, {0, 1}}, {EAST, {1, 0}}, {WEST, {-1, 0}}};

class Compare {
public:
  bool operator()(const Node &a, const Node &b) { return a.cost > b.cost; }
};

vector<Dir> getNextDirs(const Node &n, const vector<vector<int>> &grid) {
  vector<Dir> res;

  switch (n.dir) {
  case NORTH:
  case SOUTH:
    res.emplace_back(EAST);
    res.emplace_back(WEST);
    break;
  case EAST:
  case WEST:
    res.emplace_back(NORTH);
    res.emplace_back(SOUTH);
    break;
  }

  if (n.stepCount < 3) {
    res.emplace_back(n.dir);
  }

  return res;
}

vector<Dir> getNextDirs2(const Node &n, const vector<vector<int>> &grid) {
  vector<Dir> res;

  if (n.stepCount >= 4) {
    switch (n.dir) {
    case NORTH:
    case SOUTH:
      res.emplace_back(EAST);
      res.emplace_back(WEST);
      break;
    case EAST:
    case WEST:
      res.emplace_back(NORTH);
      res.emplace_back(SOUTH);
      break;
    }
  }

  if (n.stepCount < 10) {
    res.emplace_back(n.dir);
  }

  return res;
}
} // namespace

void day17() {
  auto grid = utils::parseIntoIntVecVec("../inputs/17a.txt");
  Coord end(grid[0].size() - 1, grid.size() - 1);

  {
    // keep track of visited coords
    set<tuple<Coord, Dir, int>> visited;

    // keep track of nodes to visit
    priority_queue<Node, vector<Node>, Compare> toVisit;
    toVisit.emplace(Coord{1, 0}, grid[0][1], EAST, 1);
    toVisit.emplace(Coord{0, 1}, grid[1][0], SOUTH, 1);

    while (!toVisit.empty()) {
      auto currNode = toVisit.top();

      if (currNode.coord == end) {
        cout << "part1: " << currNode.cost << endl;
		break;
      }

      if (visited.contains(
              make_tuple(currNode.coord, currNode.dir, currNode.stepCount))) {
        toVisit.pop();
        continue;
      }

      visited.emplace(currNode.coord, currNode.dir, currNode.stepCount);
      toVisit.pop();

      auto nextDirs = getNextDirs(currNode, grid);
      for (auto &nextDir : nextDirs) {
        Coord nextCoord(currNode.coord.first + dirToMovement[nextDir].first,
                        currNode.coord.second + dirToMovement[nextDir].second);

        // bounds checking
        if (nextCoord.second >= grid.size() || nextCoord.second < 0 ||
            nextCoord.first >= grid[nextCoord.second].size() ||
            nextCoord.first < 0) {
          continue;
        }

        toVisit.emplace(
            nextCoord, grid[nextCoord.second][nextCoord.first] + currNode.cost,
            nextDir, currNode.dir == nextDir ? currNode.stepCount + 1 : 1);
      }
    }
  }

  {
    // keep track of visited coords
    set<tuple<Coord, Dir, int>> visited;

    // keep track of nodes to visit
    priority_queue<Node, vector<Node>, Compare> toVisit;
    toVisit.emplace(Coord{1, 0}, grid[0][1], EAST, 1);
    toVisit.emplace(Coord{0, 1}, grid[1][0], SOUTH, 1);

    while (!toVisit.empty()) {
      auto currNode = toVisit.top();

      if (currNode.coord == end) {
        cout << "part2: " << currNode.cost << endl;
        break;
      }

      if (visited.contains(
              make_tuple(currNode.coord, currNode.dir, currNode.stepCount))) {
        toVisit.pop();
        continue;
      }

      visited.emplace(currNode.coord, currNode.dir, currNode.stepCount);
      toVisit.pop();

      auto nextDirs = getNextDirs2(currNode, grid);
      for (auto &nextDir : nextDirs) {
        Coord nextCoord(currNode.coord.first + dirToMovement[nextDir].first,
                        currNode.coord.second + dirToMovement[nextDir].second);

        // bounds checking
        if (nextCoord.second >= grid.size() || nextCoord.second < 0 ||
            nextCoord.first >= grid[nextCoord.second].size() ||
            nextCoord.first < 0) {
          continue;
        }

        toVisit.emplace(
            nextCoord, grid[nextCoord.second][nextCoord.first] + currNode.cost,
            nextDir, currNode.dir == nextDir ? currNode.stepCount + 1 : 1);
      }
    }
  }
}
