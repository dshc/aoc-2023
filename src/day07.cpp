#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using ll = unsigned long long;

const map<char, int> letterRanks{
    {'2', 0}, {'3', 1}, {'4', 2}, {'5', 3},  {'6', 4},  {'7', 5}, {'8', 6},
    {'9', 7}, {'T', 8}, {'J', 9}, {'Q', 10}, {'K', 11}, {'A', 12}};

const map<char, int> letterRanks2{
    {'2', 0}, {'3', 1}, {'4', 2},  {'5', 3},  {'6', 4},  {'7', 5}, {'8', 6},
    {'9', 7}, {'T', 8}, {'J', -1}, {'Q', 10}, {'K', 11}, {'A', 12}};

int compareCards(char l, char r) {
  if (l == r)
    return 0;
  if (letterRanks.at(l) < letterRanks.at(r)) {
    return -1;
  }
  return 1;
}

int compareCards2(char l, char r) {
  if (l == r)
    return 0;
  if (letterRanks2.at(l) < letterRanks2.at(r)) {
    return -1;
  }
  return 1;
}

struct Hand {
  string cards;
  int counts[13] = {0};
  ll bid;
  bool joker;

  Hand(string c, int b, bool joker = false) : cards(c), bid(b) {}

  bool operator<(const Hand &other) {
    if (counts[0] < other.counts[0])
      return true;
    if (counts[0] > other.counts[0])
      return false;
    if (counts[1] < other.counts[1])
      return true;
    if (counts[1] > other.counts[1])
      return false;

    for (int i = 0; i < 5; ++i) {
      auto r = joker ? compareCards2(cards[i], other.cards[i])
                     : compareCards(cards[i], other.cards[i]);
      if (r < 0)
        return true;
      if (r > 0)
        return false;
    }
    return false;
  }
};

vector<Hand> parseIntoHands() {
  ifstream f("../inputs/07a.txt");
  string l;
  vector<Hand> hands;
  while (getline(f, l)) {
    istringstream ss(l);
    string cards;
    ll bid;
    ss >> cards >> bid;
    Hand h(cards, bid);
    for (const char &c : cards) {
      if (isdigit(c)) {
        ++(h.counts[c - '0' - 2]);
        continue;
      }

      switch (c) {
      case 'T':
        ++h.counts[8];
        break;
      case 'J':
        ++h.counts[9];
        break;
      case 'Q':
        ++h.counts[10];
        break;
      case 'K':
        ++h.counts[11];
        break;
      case 'A':
        ++h.counts[12];
        break;
      default:
        break;
      }
    }
    sort(begin(h.counts), end(h.counts), greater<int>());
    hands.emplace_back(h);
  }

  return hands;
}

vector<Hand> parseIntoHands2() {
  ifstream f("../inputs/07a.txt");
  string l;
  vector<Hand> hands;
  while (getline(f, l)) {
    istringstream ss(l);
    string cards;
    ll bid;
    ss >> cards >> bid;
    Hand h(cards, bid, true);
    for (const char &c : cards) {
      if (isdigit(c)) {
        ++(h.counts[c - '0' - 2]);
        continue;
      }

      switch (c) {
      case 'T':
        ++h.counts[8];
        break;
      case 'J':
        ++h.counts[9];
        break;
      case 'Q':
        ++h.counts[10];
        break;
      case 'K':
        ++h.counts[11];
        break;
      case 'A':
        ++h.counts[12];
        break;
      default:
        break;
      }
    }
    // take any J's and add to other letters
    int jCount = h.counts[9];
    h.counts[9] = 0;
    sort(begin(h.counts), end(h.counts), greater<int>());

    for (int i = 0; i < jCount; ++i) {
      if (h.counts[0] < 5) {
        ++h.counts[0];
      } else {
        ++h.counts[1];
      }
    }

    hands.emplace_back(h);
  }

  return hands;
}

void day07part1() {
  auto hands = parseIntoHands();

  sort(begin(hands), end(hands));

  ll sum = 0;
  for (int i = 0; i < hands.size(); ++i) {
    sum += (i + 1) * hands[i].bid;
  }

  cout << "part1: " << sum << endl;
}

void day07part2() {
  auto hands = parseIntoHands2();

  sort(begin(hands), end(hands));

  ll sum = 0;
  for (int i = 0; i < hands.size(); ++i) {
    sum += (i + 1) * hands[i].bid;
  }

  cout << "part2: " << sum << endl;
}
