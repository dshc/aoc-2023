#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

using ll = long long;

void day05() {
  ifstream f("../inputs/05a.txt");
  string l;
  getline(f, l);

  vector<tuple<ll, ll, bool>> seeds;

  // parse seeds
  string tmp;
  istringstream ss{l};
  ss >> tmp >> tmp;
  while (ss) {
    seeds.emplace_back(stoll(tmp), stoll(tmp), false);
    ss >> tmp;
  }

  while (getline(f, l)) {
    if (l.empty() || !isdigit(l[0])) {
      for (auto &[seed, loc, found] : seeds) {
        found = false;
      }
      continue;
    }

    istringstream ss2{l};
    ll dest, source, amt;
    ss2 >> dest >> source >> amt;

    for (auto &[seed, loc, found] : seeds) {
      if (!found && loc >= source && loc < (source + amt)) {
        found = true;
        loc = dest + (loc - source);
      }
    }
  }

  ll min = LONG_LONG_MAX;
  for (auto &[seed, loc, _] : seeds) {
    if (loc < min)
      min = loc;
  }
  cout << "part1: " << min << endl;
}
