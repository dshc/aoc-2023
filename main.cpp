#include "src/day01.h"
#include "src/day02.h"
#include "src/day03.h"
#include "src/day04.h"

#include <chrono>
#include <iostream>

void day05();

int main() {
  using std::chrono::duration_cast;
  using std::chrono::high_resolution_clock;
  using std::chrono::microseconds;

  auto beginTime = std::chrono::high_resolution_clock::now();

  // day01::part1();
  // day01::part2();
  // day02::part1();
  // day02::part2();
  // day03::part1();
  // day03::part2();
  // day04::exec();
  day05();

  auto endTime = high_resolution_clock::now();

  std::cout << "timing (µs): "
            << duration_cast<microseconds>(endTime - beginTime).count()
            << std::endl;
}
