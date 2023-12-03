#include "day03.h"
#include "utils.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace {
using day03::Coord;

bool isSymbol(char c, bool gearsOnly = false) {
  if (gearsOnly) {
    return c == '*';
  }
  return !std::isdigit(c) && c != '.';
}

std::vector<std::vector<char>> parseInputInto2DVec(const std::string &file) {
  std::vector<std::vector<char>> out;
  std::ifstream f("../inputs/03a.txt");
  std::string l;

  while (std::getline(f, l)) {
    auto &chars = out.emplace_back(std::vector<char>{});
    for (auto &c : l) {
      chars.emplace_back(c);
    }
  }

  return out;
}

void findSymbols(std::set<Coord> &symbols, const std::string &file,
                 bool findGearsOnly = false) {
  std::ifstream f(file);
  std::string l;

  int y = 0;
  while (std::getline(f, l)) {
    int x = 0;
    for (auto &c : l) {
      if (isSymbol(c, findGearsOnly)) {
        symbols.emplace(x, y);
      }
      ++x;
    }
    ++y;
  }
}

bool neighborsSymbol(const std::set<Coord> &symbols, int x, int y) {
  int v[] = {-1, 0, 1};
  for (auto xx : v) {
    for (auto yy : v) {
      if (symbols.contains(Coord(x + xx, y + yy))) {
        return true;
      }
    }
  }
  return false;
}

std::vector<Coord> &getNeighborGears(std::vector<Coord> &out,
                                     const std::set<Coord> &gears, int x,
                                     int y) {
  int v[] = {-1, 0, 1};
  for (auto xx : v) {
    for (auto yy : v) {
      if (gears.contains(Coord(x + xx, y + yy))) {
        out.emplace_back(x + xx, y + yy);
      }
    }
  }
  return out;
}
} // namespace

void day03::part1() {
  auto file = "../inputs/03a.txt";
  int sum = 0;

  std::set<Coord> symbols;
  findSymbols(symbols, file);

  auto input = parseInputInto2DVec(file);

  // loop through each line. for each number, check if there are any
  // symbols around. If so, add the number to the sum.
  for (int y = 0; y < input.size(); ++y) {
    std::stringstream ss;
    bool addToSum = false;
    for (int x = 0; x < input[y].size(); ++x) {
      char c = input[y][x];
      if (std::isdigit(c)) {
        ss << c;
        if (!addToSum && neighborsSymbol(symbols, x, y)) {
          addToSum = true;
        }
      } else {
        if (addToSum && ss.rdbuf()->in_avail() > 0) {
          int toAdd = std::stoi(ss.str());
          sum += toAdd;
        }
        ss.str(std::string{});
        addToSum = false;
      }
    }

    // handle case where the line ends with a number
    if (addToSum && ss.rdbuf()->in_avail() > 0) {
      sum += std::stoi(ss.str());
    }
  }

  std::cout << sum << std::endl;
}

void day03::part2() {
  auto file = "../inputs/03a.txt";
  int sum = 0;

  std::map<Coord, std::set<int>> symbolsToInt;

  std::set<Coord> symbols;
  findSymbols(symbols, file, true);

  for (auto &s : symbols) {
    symbolsToInt.emplace(s, std::set<int>{});
  }

  auto input = parseInputInto2DVec(file);

  for (int y = 0; y < input.size(); ++y) {
    std::stringstream ss;
    std::vector<Coord> neighborGears;
    for (int x = 0; x < input[y].size(); ++x) {
      char c = input[y][x];
      if (std::isdigit(c)) {
        ss << c;
        getNeighborGears(neighborGears, symbols, x, y);
      } else {
        // add number to symbols int map
        if (ss.rdbuf()->in_avail() > 0) {
          for (auto &gear : neighborGears) {
            symbolsToInt.at(gear).emplace(std::stoi(ss.str()));
          }
        }

        ss.str(std::string{});
        neighborGears.clear();
      }
    }

    // handle case where the line ends with a number
    if (ss.rdbuf()->in_avail() > 0) {
      for (auto &gear : neighborGears) {
        symbolsToInt.at(gear).emplace(std::stoi(ss.str()));
      }
    }
  }

  for (const auto &[gear, vecOfInts] : symbolsToInt) {
    if (vecOfInts.size() == 2) {
      sum += std::accumulate(vecOfInts.begin(), vecOfInts.end(), 1,
                             std::multiplies<>());
    }
  }

  std::cout << sum << std::endl;
}
