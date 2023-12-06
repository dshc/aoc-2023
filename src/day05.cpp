#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

using ll = unsigned long long;

void day05part1() {
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

void parseMap(ifstream &f, vector<tuple<ll, ll, ll>> &output) {
  string l;

  while (getline(f, l)) {
    if (l.empty()) {
      return;
    }

    if (!isdigit(l[0])) {
      continue;
    }

    istringstream ss2{l};
    ll dest, source, amt;
    ss2 >> dest >> source >> amt;

    output.emplace_back(dest, source, amt);
  }
}

void day05part2() {
  ifstream f("../inputs/05a.txt");
  string l;
  getline(f, l);

  vector<pair<ll, ll>> seedRanges;
  // parse seeds
  string tmp;
  istringstream ss{l};
  ll seedNumber, range;
  ss >> tmp >> seedNumber >> range;
  while (ss) {
    seedRanges.emplace_back(seedNumber, seedNumber + range);
    ss >> seedNumber >> range;
  }

  vector<tuple<ll, ll, ll>> seedToSoil;
  vector<tuple<ll, ll, ll>> soilTofert;
  vector<tuple<ll, ll, ll>> fertToWater;
  vector<tuple<ll, ll, ll>> waterToLight;
  vector<tuple<ll, ll, ll>> lightToTemp;
  vector<tuple<ll, ll, ll>> tempToHum;
  vector<tuple<ll, ll, ll>> humToLoc;

  // parse maps
  getline(f, l);
  parseMap(f, seedToSoil);
  parseMap(f, soilTofert);
  parseMap(f, fertToWater);
  parseMap(f, waterToLight);
  parseMap(f, lightToTemp);
  parseMap(f, tempToHum);
  parseMap(f, humToLoc);

  ll min = LONG_LONG_MAX;

  for (auto &[start, end] : seedRanges) {
    cout << "next range: " << start << " " << end << endl;
    for (ll i = start; i < end; ++i) {
      ll loc = i;

      auto run = [&loc](const vector<tuple<ll, ll, ll>> &map) {
        for (auto &[dest, source, amt] : map) {
          if (loc >= source && loc < (source + amt)) {
            loc = dest + (loc - source);
            return;
          }
        }
      };

      run(seedToSoil);
      run(soilTofert);
      run(fertToWater);
      run(waterToLight);
      run(lightToTemp);
      run(tempToHum);
      run(humToLoc);

      if (loc < min)
        min = loc;
    }
  }

  cout << "part2: " << min << endl;
}
