cmake_minimum_required(VERSION 3.16)

project(aoc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(aoc
	main.cpp
	src/day01.cpp
	src/day02.cpp
	src/day03.cpp
	src/day04.cpp
	src/day05.cpp
)
