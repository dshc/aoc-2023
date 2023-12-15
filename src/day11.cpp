#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using Coord = pair<ll, ll>;

const ll part1_expansion = 1;
const ll part2_expansion = 1000000 - 1;

ll exec(ll expansion) {
  vector<Coord> galaxies;
  set<ll> galaxiesInXDir;

  ifstream f("../inputs/11a.txt");
  ll currY = 0;
  ll xlength = 0;
  for (string l; getline(f, l);) {
    if (xlength == 0)
      xlength = l.size();

    if (l.find('#') == string::npos) {
      // expand the universe vertically
      for (auto &g : galaxies) {
        g.second -= expansion;
      }
    } else {
      for (ll currX = 0; currX < l.size(); ++currX) {
        if (l[currX] == '#') {
          galaxies.emplace_back(currX, currY);
          galaxiesInXDir.emplace(currX);
        }
      }
    }

    ++currY;
  }

  // expland the universe horizontally
  for (ll x = 0; x < xlength; ++x) {
    if (!galaxiesInXDir.contains(x)) {
      for (auto &g : galaxies) {
        if (g.first < x) {
          g.first -= expansion;
        }
      }
    }
  }

  ll result = 0;

  for (ll x = 0; x < galaxies.size() - 1; ++x) {
    for (ll y = x + 1; y < galaxies.size(); ++y) {
      auto &a = galaxies[x];
      auto &b = galaxies[y];

      // manhattan distance
      auto distance = abs(a.first - b.first) + abs(a.second - b.second);

      result += distance;
    }
  }

  return result;
}

void day11() {
  cout << "part1: " << exec(part1_expansion) << endl;
  cout << "part2: " << exec(part2_expansion) << endl;
}
