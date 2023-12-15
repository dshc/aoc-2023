#include "src/day01.h"
#include "src/day02.h"
#include "src/day03.h"
#include "src/day04.h"

#include <chrono>
#include <iostream>

void day05part1();
void day05part2();
void day06part1();
void day06part2();
void day07part1();
void day07part2();
void day08part1();
void day08part2();
void day09part1();
void day09part2();
void day10part1();

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
  // day05part1();
  // day05part2();
  // day06part1();
  // day06part2();
  // day07part1();
  // day07part2();
  // day08part2();
  // day09part1();
  // day09part2();
  day10part1();

  auto endTime = high_resolution_clock::now();

  std::cout << "timing (µs): "
            << duration_cast<microseconds>(endTime - beginTime).count()
            << std::endl;
}
