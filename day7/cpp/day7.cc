#include <charconv>
#include <unordered_map>
#include <vector>
#include <ranges>
#include <string>
#include <string_view>
#include "aoc.h"

auto part1(std::string_view data) -> size_t {

  return 0;

}

auto part2(std::string_view data) -> size_t {

}

auto main() -> int {

  auto content = get_file_as_string("../data.txt");

  printf("silver: %lu\n", part1(content));
  printf("silver: %lu\n", part2(content));
  return 0;
}
