#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

void day06part1() {
  ifstream f("../inputs/06a.txt");
  string l;
  vector<int> times;
  vector<int> records;

  {
    getline(f, l);
    istringstream ss{l};
    string tmp;
    ss >> tmp >> tmp;
    while (ss) {
      times.emplace_back(stoi(tmp));
      ss >> tmp;
    }
  }

  {
    getline(f, l);
    istringstream ss{l};
    string tmp;
    ss >> tmp >> tmp;
    while (ss) {
      records.emplace_back(stoi(tmp));
      ss >> tmp;
    }
  }

  vector<int> results(static_cast<int>(times.size()));

  for (int i = 0; i < times.size(); ++i) {
    for (int timeHeld = 0; timeHeld <= times[i]; ++timeHeld) {
      if ((timeHeld * (times[i] - timeHeld)) > records[i]) {
        ++results[i];
      }
    }
  }

  cout << "part1: "
       << accumulate(results.begin(), results.end(), 1, multiplies<>()) << endl;
}

void day06part2() {
  using ll = unsigned long long;
  ifstream f("../inputs/06b.txt");
  string l;
  vector<ll> times;
  vector<ll> records;

  {
    getline(f, l);
    istringstream ss{l};
    string tmp;
    ss >> tmp >> tmp;
    while (ss) {
      times.emplace_back(stoll(tmp));
      ss >> tmp;
    }
  }

  {
    getline(f, l);
    istringstream ss{l};
    string tmp;
    ss >> tmp >> tmp;
    while (ss) {
      records.emplace_back(stoll(tmp));
      ss >> tmp;
    }
  }

  vector<int> results(static_cast<int>(times.size()));

  for (int i = 0; i < times.size(); ++i) {
    for (ll timeHeld = 0; timeHeld <= times[i]; ++timeHeld) {
      if ((timeHeld * (times[i] - timeHeld)) > records[i]) {
        ++results[i];
      }
    }
  }

  cout << "part1: "
       << accumulate(results.begin(), results.end(), 1, multiplies<>()) << endl;
}
