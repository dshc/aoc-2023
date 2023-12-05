#include "day04.h"
#include "utils.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace {} // namespace

void day04::exec() {

  int sum = 0;

  std::ifstream f("../inputs/04a.txt");
  std::string l;

  std::vector<day04::Card> cards{210, Card{}};

  int currCard = 0;
  while (std::getline(f, l)) {
    int cardScore = 0;
    std::unordered_set<int> winning_numbers{};
    std::istringstream ss{l};
    std::string s;
    ss >> s >> s >> s;

    while (s != "|") {
      winning_numbers.emplace(std::stoi(s));
      ss >> s;
    }

    ss >> s;
    int num_winning = 0;
    while (ss) {
      if (winning_numbers.contains(std::stoi(s))) {
        ++num_winning;
        if (cardScore == 0) {
          cardScore = 1;
        } else {
          cardScore *= 2;
        }
      }
      ss >> s;
    }

    sum += cardScore;

    cards[currCard].winning_numbers = num_winning;
    ++cards[currCard].count;

    for (int x = 0; x < cards[currCard].count; ++x) {
      for (int i = currCard + 1; i < currCard + num_winning + 1; ++i) {
        ++cards[i].count;
      }
    }

    ++currCard;
  }

  std::cout << "part1: " << sum << std::endl;

  int p2sum = 0;
  for (auto &c : cards) {
    p2sum += c.count;
  }
  std::cout << "part2: " << p2sum << std::endl;
}
