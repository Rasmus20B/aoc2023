#include <chrono>
#include <thread>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <thread>
#include <ranges>
#include <iostream>


#include "aoc.h"

size_t getFirstAndLast(std::string_view s) {
    auto res = s
      | std::views::filter([](char c) {
              return (c - '0' > 0 && c - '0' < 10);
              });
    std::string nums(res.begin(), res.end());
    if(nums.size() == 0) return 0;
    std::string incr = std::string(1, nums[0]) + nums[nums.size() - 1];
    return stoi(incr);
}

auto part2_mp(std::string_view content) -> size_t {

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

  auto lines = content
    | std::views::split('\n');

  std::vector<std::string_view> lines_s(lines.begin(), lines.end());

  auto n_t = std::thread::hardware_concurrency();
  std::vector<std::thread> pool;
  pool.reserve(n_t);

  std::atomic<size_t> sum{0};

  auto worker = [&](const size_t s, const size_t e) {
    // std::cout << "Thread " << std::this_thread::get_id() << ": Start = " << s << ", End = " << e << "\n";
    for(auto l : std::span(lines_s.begin() + s, lines_s.begin() + e)) {
      std::string corrected = "";
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
      sum.fetch_add(stoi(incr));
      corrected.clear();
    }
  };

  size_t start = 0;
  for(int i = 0; i < n_t; ++i) {
    size_t end = start + (lines_s.size() / n_t) ;
    pool.emplace_back(worker, start, end);
    start = end ;
  }

  for(auto &t : pool) {
    t.join();
  }
  return sum;
}

auto part1_mp(std::string_view content) -> size_t {

  auto lines = content
    | std::views::split('\n');

  std::vector<std::string_view> lines_s(lines.begin(), lines.end());

  auto n_t = std::thread::hardware_concurrency();
  std::vector<std::thread> pool;
  pool.reserve(n_t);

  std::atomic<size_t> sum{0};

  auto worker = [&](const size_t s, const size_t e) {
    for(auto l : std::span(lines_s.begin() + s, lines_s.begin() + e)) {
      sum.fetch_add(std::move(getFirstAndLast(std::string(l.begin(), l.end()))));
    }
  };

  size_t start = 0;
  for(int i = 0; i < n_t; ++i) {
    size_t end = start + (lines_s.size() / n_t) ;
    pool.emplace_back(worker, start, end);
    start = end ;
  }

  for(auto &t : pool) {
    t.join();
  }
  return sum;
}

auto part1(std::string_view content, size_t sum = 0) -> size_t {

  auto lines = content
    | std::views::split('\n');

  std::for_each(lines.begin(), lines.end(), [&](const auto l){
    sum += getFirstAndLast(std::string(l.begin(), l.end()));
  });    

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
  return sum;
}

auto main() -> int {
  {
  auto start = std::chrono::high_resolution_clock::now();
  auto res = part1(get_file_as_string("../data"));
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Part1   : " << res << " in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us.\n";
  }

  {
  auto start = std::chrono::high_resolution_clock::now();
  auto res = part1_mp(get_file_as_string("../data"));
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Part1 MP: " << res << " in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us.\n";
  }

  {
  auto start = std::chrono::high_resolution_clock::now();
  auto res = part2(get_file_as_string("../data"));
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Part2   : " << res << " in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us.\n";
  }

  {
  auto start = std::chrono::high_resolution_clock::now();
  auto res = part2_mp(get_file_as_string("../data"));
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Part2 MP: " << res << " in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us.\n";
  }
  return 0;
}
