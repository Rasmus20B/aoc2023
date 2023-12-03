#include <cassert>
#include <charconv>
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <ranges>
#include <span>
#include <vector>

#include "aoc.h"

static constexpr std::array<std::array<int8_t, 2>, 8> dirs = {{
  {-1, 1},
  {0, -1},
  {1, 0},
  {1, 1},
  {1, -1},
  {-1, 0},
  {0, 1},
  {-1, -1},
}};

auto is_valid_symbol(char c) {
  return c >= '!' && c < '.' ||
          c == '/' ||
          c >= ':' && c < 'A';
}

auto is_num_char(const char c) {
  return c >= '0' && c <= '9';
}

auto is_within_field(uint16_t width, uint16_t height, uint16_t x, uint16_t y) -> bool {
  return x >= 0 && x < width && y >= 0 && y < height;
}

auto part1(std::string_view data) -> size_t {

  size_t sum = 0;
  auto lines = data | std::views::split('\n');
  std::vector<std::string_view> grid(lines.begin(), lines.end());
  auto n = grid.size();
  auto m = grid[0].size();
  std::vector<std::vector<bool>> visits(n, std::vector<bool>(m, false));

  for(size_t i = 0; i < grid.size(); ++i) {
    for(size_t j = 0; j < grid[0].size(); ++j) {
      if(is_valid_symbol(grid[i][j])) {
        for(auto d : dirs) {
          auto cx = i + d[0];
          auto cy = j + d[1];

          auto cur = grid[cx][cy];

          if(is_within_field(n, m, cx, cy)) {
            if(is_num_char(grid[cx][cy]) && 
                  visits[cx][cy] == false) {
              size_t num = 0;
              uint16_t start = cy;
              while(is_within_field(n, m, cx, cy)
                  && is_num_char(grid[cx][cy])) {
                visits[cx][cy] = true;
                cy--;
              }
              uint16_t left = cy + 1;

              cy = start + 1;
              while(is_within_field(n, m, cx, cy) &&
                  is_num_char(grid[cx][cy])) {
                visits[cx][cy] = true;
                cy++;
              }
              uint16_t right = cy - 1;
              cy = left;
              num = grid[cx][left] - '0';
              while(cy < right) {
                cy++;
                num = (num * 10) + (grid[cx][cy] - '0');
              }
              sum += num;
            }
          } 
        }
      }
    }
  }

  return sum;
}

auto part2(std::string_view data) -> size_t {

  size_t sum = 0;
  auto lines = data | std::views::split('\n');
  std::vector<std::string_view> grid(lines.begin(), lines.end());
  auto n = grid.size();
  auto m = grid[0].size();
  std::vector<std::vector<bool>> visits(n, std::vector<bool>(m, false));

  for(size_t i = 0; i < grid.size(); ++i) {
    for(size_t j = 0; j < grid[0].size(); ++j) {
      if(is_valid_symbol(grid[i][j])) {
        std::vector<uint32_t> nums;
        for(auto d : dirs) {
          auto cx = i + d[0];
          auto cy = j + d[1];

          auto cur = grid[cx][cy];

          if(is_within_field(n, m, cx, cy)) {
            if(is_num_char(grid[cx][cy]) && 
                  visits[cx][cy] == false) {
              size_t num = 0;
              uint16_t start = cy;
              while(is_within_field(n, m, cx, cy)
                  && is_num_char(grid[cx][cy])) {
                visits[cx][cy] = true;
                cy--;
              }
              uint16_t left = cy + 1;

              cy = start + 1;
              while(is_within_field(n, m, cx, cy) &&
                  is_num_char(grid[cx][cy])) {
                visits[cx][cy] = true;
                cy++;
              }
              uint16_t right = cy - 1;
              cy = left;
              num = grid[cx][left] - '0';
              while(cy < right) {
                cy++;
                num = (num * 10) + (grid[cx][cy] - '0');
              }
              nums.emplace_back(num);
            }
          } 
        }
        if(nums.size() == 2) {
          sum += nums[0] * nums[1];
        }
      }
    }
  }

  return sum;
}

#define P1_TEST "467..114..\n\
...*......\n\
..35..633.\n\
......#...\n\
617*......\n\
.....+.58.\n\
..592.....\n\
......755.\n\
...$.*....\n\
.664.598.."

auto main() -> int {

  auto res1 = part1(P1_TEST);
  std::cout << "part1: " << res1 << " == " << 4361 << "\n";
  assert(res1 == 4361);

  auto res2 = part2(P1_TEST);
  std::cout << "part2: " << res2 << " == " << 467835 << "\n";
  assert(res2 == 467835);
  {
  auto start = std::chrono::high_resolution_clock::now();
  auto res = part1(get_file_as_string("../data"));
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Silver   : " << res << " in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us.\n";
  }


  {
  auto start = std::chrono::high_resolution_clock::now();
  auto res = part2(get_file_as_string("../data"));
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Gold   : " << res << " in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us.\n";
  }

  return 0;
}
