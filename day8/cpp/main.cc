
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_map>

#include "aoc.h"

auto part1(std::string_view data) -> size_t {

  auto splits = data 
    | std::views::split('\n');

  std::vector<std::string_view> lines(splits.begin(), splits.end());

  auto dirs = lines[0];

  std::unordered_map<std::string_view,  std::vector<std::string_view>> graph;

  for(auto l : std::span(lines.begin() + 2, lines.end()) ) {
    auto halves = l | std::views::split('=');
    std::string_view full(
    graph.insert({ l})
  }

  return 0;
}

auto main() -> int {

  auto content = get_file_as_string("../data.txt");

  printf("%lu\n", part1(content));
  return 0;
}
