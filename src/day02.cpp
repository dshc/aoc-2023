#include "day02.h"
#include "utils.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace {} // namespace

void day02::part1() {
  int sum = 0;
  std::unordered_map<std::string, int> max{
      {"red", 12}, {"green", 13}, {"blue", 14}};

  std::ifstream f("../inputs/02a.txt");
  std::string l;

  int gameNumber = 1;
  while (std::getline(f, l)) {
    std::size_t start = l.find(": ");
    std::stringstream ss(l.substr(start + 2));
    std::string gameLine;
    int isPossible = true;
    while (std::getline(ss, gameLine, ';')) {
      utils::trim(gameLine);
      std::stringstream ss2(gameLine);
      std::string x;
      while (std::getline(ss2, x, ',')) {
        utils::trim(x);
        auto pair = utils::splitAndMakePair(x);
        if (std::stoi(pair.first) > max.at(pair.second)) {
          isPossible = false;
          break;
        }
      }
    }
    if (isPossible) {
      sum += gameNumber;
    }
    ++gameNumber;
  }

  std::cout << sum << std::endl;
}

void day02::part2() {
  std::unordered_map<std::string, int> index{
      {"red", 0}, {"green", 1}, {"blue", 2}};
  int sum = 0;
  std::ifstream f("../inputs/02a.txt");
  std::string l;
  while (std::getline(f, l)) {
    std::vector<int> colorsMax{0, 0, 0};

    std::size_t start = l.find(": ");
    std::stringstream ss(l.substr(start + 2));
    std::string gameLine;
    while (std::getline(ss, gameLine, ';')) {
      utils::trim(gameLine);
      std::stringstream ss2(gameLine);
      std::string x;
      while (std::getline(ss2, x, ',')) {
        utils::trim(x);
        auto pair = utils::splitAndMakePair(x);
        if (std::stoi(pair.first) > colorsMax[index.at(pair.second)]) {
          colorsMax[index.at(pair.second)] = std::stoi(pair.first);
        }
      }
    }

    sum += std::accumulate(colorsMax.begin(), colorsMax.end(), 1,
                           std::multiplies<>());
  }
  std::cout << sum << std::endl;
}
