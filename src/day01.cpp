#include "day01.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

namespace {

void replaceWordToNumberEquivalent(std::string &in) {
  in = std::regex_replace(in, std::regex("one"), "o1e");
  in = std::regex_replace(in, std::regex("two"), "t2o");
  in = std::regex_replace(in, std::regex("three"), "t3e");
  in = std::regex_replace(in, std::regex("four"), "f4r");
  in = std::regex_replace(in, std::regex("five"), "f5e");
  in = std::regex_replace(in, std::regex("six"), "s6x");
  in = std::regex_replace(in, std::regex("seven"), "s7n");
  in = std::regex_replace(in, std::regex("eight"), "e8t");
  in = std::regex_replace(in, std::regex("nine"), "n9e");
}

void sumUp(const std::string &l, int &sum) {
  auto frontIter = l.begin();
  auto backIter = l.end();

  for (auto i = l.begin(); i != l.end(); ++i) {
    if (std::isdigit(*i)) {
      sum += ((*i) - '0') * 10;
      break;
    }
  }

  for (auto i = l.rbegin(); i != l.rend(); ++i) {
    if (std::isdigit(*i)) {
      sum += ((*i) - '0');
      break;
    }
  }
}

} // namespace

void day01::part1() {
  int sum = 0;
  std::ifstream f("../inputs/01a.txt");
  std::string l;
  while (std::getline(f, l)) {
    sumUp(l, sum);
  }
  std::cout << sum << std::endl;
}

void day01::part2() {
  int sum = 0;
  std::ifstream f("../inputs/01a.txt");
  std::string l;
  while (std::getline(f, l)) {
    replaceWordToNumberEquivalent(l);
    sumUp(l, sum);
  }
  std::cout << sum << std::endl;
}
