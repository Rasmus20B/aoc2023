

#include <cassert>
#include <cmath>
#include <cstdint>
#include <future>
#include <thread>
#include <iostream>
#include <string>
#include <string_view>
#include <ranges>
#include <unordered_map>
#include <unordered_set>

#include "aoc.h"

[[gnu::const]]
auto calc_distances(const std::vector<int64_t>& dim, const int multiple) -> size_t {
  int64_t sum = 0;
  int64_t empty = 0;
  int64_t p = 0;
  for(auto d: dim) {
    sum += d * empty;
    p += d;
    auto m = ((d == 0) * multiple) + 1;
    empty += p * std::min(m, multiple);
  }
  return sum;
}

auto part1(std::string_view data, int multiple) -> size_t {

  auto lines = data
    | std::views::split('\n');

  std::vector<std::string_view> universe(lines.begin(), lines.end());

  std::vector<int64_t> rows(universe.size(), 0);
  std::vector<int64_t> cols(universe[0].size(), 0);

  for(size_t i = 0; i < rows.size(); ++i) {
    for(size_t j = 0; j < cols.size(); ++j) {
      if(universe[i][j] == '.') [[likely]]{
        continue;
      }
      rows[i]++;
      cols[j]++;
    }
  }
  return calc_distances(rows, multiple) + calc_distances(cols, multiple);
}


auto main() -> int {
  auto content = get_file_as_string("../data.txt");
  assert(part1(content, 2) == 17341358);
  assert(part1(content, 1000000) == 805925729538);
  // printf("%ld\n", part1("...#......\n.......#..\n#.........\n..........\n......#...\n.#........\n.........#\n..........\n.......#..\n#...#.....", 2));
  // printf("%ld\n", part1("...#......\n.......#..\n#.........\n..........\n......#...\n.#........\n.........#\n..........\n.......#..\n#...#.....", 1000000));
  // std::cout << "Silver: " << part1(content, 2) << "\n";
  // std::cout << "Gold: " << part1(content, 1000000) << "\n";

  return 0;
}

