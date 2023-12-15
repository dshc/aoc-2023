#include "utils.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int getHash(const string &s) {
  int res = 0;
  for (auto c : s) {
    res += int(c);
    res *= 17;
    res = res % 256;
  }
  return res;
}

struct Box {
  vector<pair<string, int>> elements;
};

void day15() {
  ifstream f("../inputs/15a.txt");
  string l;
  f >> l;
  auto hashes = utils::split(l, ',');

  int sum = 0;
  for (auto &h : hashes)
    sum += getHash(h);

  cout << "part1: " << sum << endl;

  Box boxes[256];
  for (auto &h : hashes) {
    if (h.find('-') != string::npos) {
      auto label = h.substr(0, h.size() - 1);
      auto &box = boxes[getHash(label)];
      auto f = find_if(box.elements.begin(), box.elements.end(),
                       [&label](const pair<string, int> &p) -> bool {
                         return p.first == label;
                       });
      if (f != box.elements.end()) {
        // remove
        box.elements.erase(f);
      }
    } else {
      auto x = utils::split(h, '=');
      auto &label = x[0];
      auto &box = boxes[getHash(label)];
      auto lense = stoi(x[1]);
      auto f = find_if(box.elements.begin(), box.elements.end(),
                       [&label](const pair<string, int> &p) -> bool {
                         return p.first == label;
                       });
      if (f != box.elements.end()) {
        // replace
        f->second = lense;
      } else {
        box.elements.emplace_back(make_pair(label, lense));
      }
    }
  }

  int part2res = 0;
  for (int boxNumber = 0; boxNumber < 256; ++boxNumber) {
    auto &box = boxes[boxNumber];
    for (int elemNumber = 0; elemNumber < box.elements.size(); ++elemNumber) {
      auto &elem = box.elements[elemNumber];
      part2res += (boxNumber + 1) * (elemNumber + 1) * (elem.second);
    }
  }
  cout << "part2: " << part2res << endl;
}
