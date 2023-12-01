#include <cassert>
#include <charconv>
#include <exception>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <ranges>
#include <iostream>
#include <cassert>


#include "aoc.h"


auto part1(std::string_view content) -> size_t {

  auto lines = content
    | std::views::split('\n');

  size_t sum = 0;
  for(auto l : lines) {
    auto res = l
      | std::views::filter([](char c) {
              return (c - '0' > 0 && c - '0' < 10);
              });
    std::string nums(res.begin(), res.end());
    if(nums.size() == 0) break;
    std::string incr = std::string(1, nums[0]) + nums[nums.size() - 1];
    sum += stoi(incr);
  }    

  return sum;
}

auto part2(std::string_view content) -> size_t {

  const std::unordered_map<std::string, size_t> values {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9},
  };

  size_t sum = 0;

  auto lines = content
    | std::views::split('\n');

  std::string corrected = "";
  for(auto l : lines) {
    for(size_t i = 0; i < l.size() ; ++i) {
      if(l[i] >= 'a' && l[i] <= 'z') {
        size_t j = i;
        std::string tmp("");
        while(l[j] >= 'a' && l[j] <= 'z') {
          tmp += l[j];
          auto res = values.find(tmp);
          if(res != values.end()) {
            corrected += std::to_string(res->second);
            break;
          }
          ++j;
        }
      } else {
        corrected += std::to_string(l[i] - '0');
      }
    }
    if(corrected.size() == 0) {
      break;
    }
    std::string incr = std::string(1, corrected[0]) + corrected[corrected.size() - 1];
    sum += stoi(incr);
    corrected.clear();
  }
  std::cout << sum << "\n";
  return sum;
}

auto main() -> int {
  std::cout << "Part1: " << part1(get_file_as_string("../data")) << "\n";
  std::cout << "Part2: " << part2(get_file_as_string("../data")) << "\n";
  return 0;
}
