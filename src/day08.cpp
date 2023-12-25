#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using ll = unsigned long long;

map<string, pair<string, string>> parseInput(string &directions) {
  ifstream f("../inputs/08a.txt");
  getline(f, directions);

  map<string, pair<string, string>> nodes;

  string l;
  while (getline(f, l)) {
    if (l.empty())
      continue;

    istringstream ss{l};
    string a, b, c;
    ss >> a >> b >> b >> c;
    b = b.substr(1, 3);
    c = c.substr(0, 3);

    nodes.emplace(a, make_pair(b, c));
  }
  return nodes;
}

void day08part1() {
  string directions;
  auto nodes = parseInput(directions);

  auto it = begin(directions);
  auto e = end(directions);
  string currNode = "AAA";
  int steps = 0;
  while (true) {
    if (currNode == "ZZZ") {
      break;
    }

    ++steps;
    const auto &[left, right] = nodes[currNode];
    currNode = *it == 'R' ? right : left;

    // increment direction iterator
    ++it;
    if (it == e)
      it = begin(directions);
  }

  cout << "part1: " << steps << endl;
}

void day08part2() {
  string directions;
  auto nodes = parseInput(directions);

  // find starting nodes
  vector<string> startingNodes;
  for (const auto &[n, _] : nodes) {
    if (n[2] == 'A')
      startingNodes.emplace_back(n);
  }

  auto search = [&directions, &nodes](const string &sn) {
    auto it = begin(directions);
    auto e = end(directions);
    string currNode = sn;
    ll steps = 0;
    while (true) {
      if (currNode[2] == 'Z') {
        break;
      }

      ++steps;
      const auto &[left, right] = nodes[currNode];
      currNode = *it == 'R' ? right : left;

      // increment direction iterator
      ++it;
      if (it == e)
        it = begin(directions);
    }
    return steps;
  };

  // foreach starting node find how long it would take until finding the first
  // end node
  vector<ll> x;
  cout << "{";
  for (const auto &sn : startingNodes) {
    cout << search(sn) << ",";
  }
  cout << "}" << endl;

  cout << "using wolfram alpha to compute LCM :) -- 11283670395017" << endl;
}
