#include "day01.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

namespace {

std::string replaceWordToNumberEquivalent(std::string in) {
  std::regex numbersRegex("(one|two|three|four|five|six|seven|eight|nine)");
  for (std::smatch sm; regex_search(in, sm, numbersRegex);) {
    std::string s = sm.str();
    if (s == "one") {
      in = std::regex_replace(in, std::regex("one"), "o1e");
    } else if (s == "two") {
      in = std::regex_replace(in, std::regex("two"), "t2o");
    } else if (s == "three") {
      in = std::regex_replace(in, std::regex("three"), "t3e");
    } else if (s == "four") {
      in = std::regex_replace(in, std::regex("four"), "f4r");
    } else if (s == "five") {
      in = std::regex_replace(in, std::regex("five"), "f5e");
    } else if (s == "six") {
      in = std::regex_replace(in, std::regex("six"), "s6x");
    } else if (s == "seven") {
      in = std::regex_replace(in, std::regex("seven"), "s7n");
    } else if (s == "eight") {
      in = std::regex_replace(in, std::regex("eight"), "e8t");
    } else if (s == "nine") {
      in = std::regex_replace(in, std::regex("nine"), "n9e");
    }
  }
  return in;
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
    sumUp(replaceWordToNumberEquivalent(l), sum);
  }
  std::cout << sum << std::endl;
}
