#include "utils.h"

#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void day09part1() {
  int result = 0;

  ifstream f("../inputs/09a.txt");
  for (string l; getline(f, l);) {
    vector<int> history = utils::split(l);

    auto maxIndex = history.size() - 1;

    while (true) {
      bool cont = false;
      for (int i = 0; i < maxIndex; ++i) {
        history[i] = history[i + 1] - history[i];
        if (history[i] != 0)
          cont = true;
      }
      if (!cont)
        break;
      --maxIndex;
    }

    result += accumulate(begin(history), end(history), 0);
  }

  cout << "part1: " << result << endl;
}

void day09part2() {
  int result = 0;

  ifstream f("../inputs/09a.txt");
  for (string l; getline(f, l);) {
    vector<int> history = utils::split(l);
    reverse(begin(history), end(history));

    auto maxIndex = history.size() - 1;

    while (true) {
      bool cont = false;
      for (int i = 0; i < maxIndex; ++i) {
        history[i] = history[i + 1] - history[i];
        if (history[i] != 0)
          cont = true;
      }
      if (!cont)
        break;
      --maxIndex;
    }

    result += accumulate(begin(history), end(history), 0);
  }

  cout << "part2: " << result << endl;
}
