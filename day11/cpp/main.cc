

#include <cmath>
#include <iostream>
#include <string>
#include <string_view>
#include <ranges>
#include <unordered_map>
#include <unordered_set>

#include "aoc.h"

auto part1(std::string_view data, int multiple) -> size_t {

  auto lines = data
    | std::views::split('\n');

  std::vector<std::string_view> universe(lines.begin(), lines.end());

  std::vector<int64_t> rows(universe.size(), 0);
  std::vector<int64_t> cols(universe[0].size(), 0);

  for(size_t i = 0; i < rows.size(); ++i) {
    for(size_t j = 0; j < cols.size(); ++j) {
      if(universe[i][j] == '.') {
        continue;
      }
      rows[i]++;
      cols[j]++;
    }
  }

  int64_t sum = 0;
  int64_t empty = 0;
  int64_t p = 0;
  for(auto r: rows) {
    if(r > 0) {
      sum += r * empty;
      p += r;
      empty += p;
    } else {
      empty += multiple * p;
    }
  }

  empty = 0;
  p = 0;
  for(auto c: cols) {
    if(c) {
      sum += c * empty;
      p += c;
      empty += p;
    } else {
      empty += multiple * p;
    }
  }
  return sum;
}
auto main() -> int {
  auto content = get_file_as_string("../data.txt");
  printf("%ld\n", part1("...#......\n.......#..\n#.........\n..........\n......#...\n.#........\n.........#\n..........\n.......#..\n#...#.....", 2));
  printf("%ld\n", part1("...#......\n.......#..\n#.........\n..........\n......#...\n.#........\n.........#\n..........\n.......#..\n#...#.....", 1000000));
  std::cout << "Silver: " << part1(content, 2) << "\n";
  std::cout << "Gold: " << part1(content, 1000000) << "\n";

  return 0;
}

