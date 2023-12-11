
#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include <utility>
#include <cassert>
#include <array>
#include <ranges>
#include <string_view>
#include <string>
#include <span>

#include <raylib.h>

#include "aoc.h"

int64_t part2(std::string_view data) {

  size_t result;

  return 0;

}

enum Direction {
  NORTH,
  SOUTH,
  EAST,
  WEST,
};

static constexpr std::array<std::array<int32_t, 2>, 4> dirs = {{
  {-1, 0},
  {1, 0},
  {0, 1},
  {0, -1},
}};

std::string direction_to_string(int d) {
  switch (static_cast<Direction>(d)) {
    case NORTH:
      return "North";
    case SOUTH:
      return "South";
    case EAST:
      return "East";
    case WEST:
      return "West";
    default:
      std::unreachable();
  }
}

std::pair<int64_t, int64_t> move_direction(std::pair<int64_t, int64_t> pos, Direction dir) {
  return {pos.first+dirs[static_cast<int32_t>(dir)][0], pos.second + dirs[static_cast<int32_t>(dir)][1]};
}

bool is_visited(std::pair<int64_t, int64_t> cur, Direction dir, std::vector<std::vector<bool>>& grid) {
  return grid[cur.first+dirs[dir][0]][cur.second+dirs[dir][1]];
}

std::vector<std::vector<bool>> multiply_visited(std::vector<std::vector<bool>> visited, size_t multiple) {

  std::vector<std::vector<bool>> res;

  res.resize(visited.size() * multiple);
  for(auto &i: res) {
    i.resize(visited[0].size() * multiple);
    std::fill(i.begin(), i.end(), '.');
  }

  for(int i = 0; i < visited.size(); ++i) {
    for(int j = 0; j < visited[0].size(); ++j) {
      auto hi_i = i * multiple;
      auto hi_j = j * multiple;
      if(visited[i][j] == false) {
        res[hi_i][hi_j] = false;
        res[hi_i+1][hi_j] = false;
        res[hi_i+2][hi_j] = false;
        res[hi_i][hi_j+1] = false;
        res[hi_i][hi_j+2] = false;
        res[hi_i+1][hi_j+1] = false;
        res[hi_i+2][hi_j+1] = false;
        res[hi_i+2][hi_j+2] = false;
        res[hi_i+1][hi_j+2] = false;
      } else if (visited[i][j] == true) {
        res[hi_i][hi_j] = true;
        res[hi_i+1][hi_j] = true;
        res[hi_i+2][hi_j] = true;
        res[hi_i][hi_j+1] = true;
        res[hi_i][hi_j+2] = true;
        res[hi_i+1][hi_j+1] = true;
        res[hi_i+2][hi_j+1] = true;
        res[hi_i+2][hi_j+2] = true;
      }
    }
  }
  return res;
}

std::vector<std::vector<char>> multiply_graph(std::vector<std::string_view>& grid, size_t multiple) {

  std::vector<std::vector<char>> res;

  res.resize(grid.size() * multiple);
  for(auto &i: res) {
    i.resize(grid[0].size() * multiple);
    std::fill(i.begin(), i.end(), '.');
  }

  for(int i = 0; i < grid.size(); ++i) {
    for(int j = 0; j < grid[0].size(); ++j) {
      auto hi_i = i * multiple;
      auto hi_j = j * multiple;
      if(grid[i][j] == '.') {
        res[hi_i][hi_j] = '.';
        res[hi_i+1][hi_j] = '.';
        res[hi_i+2][hi_j] = '.';
        res[hi_i][hi_j+1] = '.';
        res[hi_i][hi_j+2] = '.';
        res[hi_i+1][hi_j+1] = '.';
        res[hi_i+2][hi_j+1] = '.';
        res[hi_i+2][hi_j+2] = '.';
        res[hi_i+1][hi_j+2] = '.';
      } else if (grid[i][j] == '7') {
        res[hi_i][hi_j] = '.';
        res[hi_i+1][hi_j] = '-';
        res[hi_i+2][hi_j] = '.';
        res[hi_i][hi_j+1] = '.';
        res[hi_i][hi_j+2] = '.';
        res[hi_i+1][hi_j+1] = '7';
        res[hi_i+2][hi_j+1] = '|';
        res[hi_i+2][hi_j+2] = '.';
        res[hi_i+1][hi_j+2] = '.';
      } else if (grid[i][j] == 'J') {
        res[hi_i][hi_j] = '.';
        res[hi_i+1][hi_j] = '-';
        res[hi_i+2][hi_j] = '.';
        res[hi_i][hi_j+1] = '|';
        res[hi_i][hi_j+2] = '.';
        res[hi_i+1][hi_j+1] = 'J';
        res[hi_i+2][hi_j+1] = '.';
        res[hi_i+2][hi_j+2] = '.';
        res[hi_i+1][hi_j+2] = '.';
      } else if (grid[i][j] == 'F') {
        res[hi_i][hi_j] = '.';
        res[hi_i+1][hi_j] = '.';
        res[hi_i+2][hi_j] = '.';
        res[hi_i][hi_j+1] = '.';
        res[hi_i][hi_j+2] = '.';
        res[hi_i+1][hi_j+1] = 'F';
        res[hi_i+2][hi_j+1] = '|';
        res[hi_i+2][hi_j+2] = '.';
        res[hi_i+1][hi_j+2] = '-';
      } else if (grid[i][j] == 'L') {
        res[hi_i][hi_j] = '.';
        res[hi_i+1][hi_j] = '.';
        res[hi_i+2][hi_j] = '.';
        res[hi_i][hi_j+1] = '|';
        res[hi_i][hi_j+2] = '.';
        res[hi_i+1][hi_j+1] = 'L';
        res[hi_i+2][hi_j+1] = '.';
        res[hi_i+2][hi_j+2] = '.';
        res[hi_i+1][hi_j+2] = '-';
      } else if (grid[i][j] == 'L') {
        res[hi_i][hi_j] = '.';
        res[hi_i+1][hi_j] = '.';
        res[hi_i+2][hi_j] = '.';
        res[hi_i][hi_j+1] = '|';
        res[hi_i][hi_j+2] = '.';
        res[hi_i+1][hi_j+1] = 'L';
        res[hi_i+2][hi_j+1] = '.';
        res[hi_i+2][hi_j+2] = '.';
        res[hi_i+1][hi_j+2] = '-';
    } else if (grid[i][j] == '-') {
        res[hi_i][hi_j] = '.';
        res[hi_i+1][hi_j] = '-';
        res[hi_i+2][hi_j] = '.';
        res[hi_i][hi_j+1] = '.';
        res[hi_i][hi_j+2] = '.';
        res[hi_i+1][hi_j+1] = '-';
        res[hi_i+2][hi_j+1] = '.';
        res[hi_i+2][hi_j+2] = '.';
        res[hi_i+1][hi_j+2] = '-';
    } else if (grid[i][j] == '|') {
        res[hi_i][hi_j] = '.';
        res[hi_i+1][hi_j] = '.';
        res[hi_i+2][hi_j] = '.';
        res[hi_i][hi_j+1] = '|';
        res[hi_i][hi_j+2] = '.';
        res[hi_i+1][hi_j+1] = '|';
        res[hi_i+2][hi_j+1] = '|';
        res[hi_i+2][hi_j+2] = '.';
        res[hi_i+1][hi_j+2] = '.';
    } else if (grid[i][j] == 'S') {
        res[hi_i][hi_j] = 'S';
        res[hi_i+1][hi_j] = 'S';
        res[hi_i+2][hi_j] = 'S';
        res[hi_i][hi_j+1] = 'S';
        res[hi_i][hi_j+2] = 'S';
        res[hi_i+1][hi_j+1] = 'S';
        res[hi_i+2][hi_j+1] = 'S';
        res[hi_i+2][hi_j+2] = 'S';
        res[hi_i+1][hi_j+2] = 'S';
    }
    }
  }

  return res;
}

int64_t part1(std::string_view data) {

  size_t moves = 0;
  auto lines = data | std::views::split('\n');
  std::pair<long, long> start{};
  std::vector<std::string_view> grid(lines.begin(), lines.end());
  std::vector<std::string> grid_edit(grid.begin(), grid.end());
  std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size()));
  for(auto v: visited) {
    std::fill(v.begin(),  v.end(), false);
  }

  for(int i = 0; i < grid.size(); ++i) {
    for(int j = 0; j < grid[0].size(); ++j) {
      if (grid[i][j] == 'S') {
        start = {i, j};
      }
    }
  }
  std::cout << "Found start @: " << start.second << ", " << start.first << "\n";

  std::pair<long, long> pos = start;

  while(true) {


    visited[pos.first][pos.second] = true;
    bool next = false;

    for(int i = 0; i < dirs.size(); ++i) {

      auto direction = static_cast<Direction>(i);
      bool valid = false;
      switch(grid[pos.first][pos.second]) {
        case '|':
          if(direction == NORTH || direction == SOUTH) {
            valid = true;
          }
          break;
        case '-':
          if(direction == EAST || direction == WEST) {
            valid = true;
          }
          break;
        case 'L':
          if(direction == NORTH || direction == EAST) {
            valid = true;
          }
          break;
        case 'F':
          if(direction == EAST || direction == SOUTH) {
            valid = true;
          }
          break;
        case 'J':
          if(direction == NORTH || direction == WEST) {
            valid = true;
          }
          break;
        case '7':
          if(direction == WEST || direction == SOUTH) {
            valid = true;
          }
          break;
        case 'S':
          valid = true;
          break;
        default:
          std::unreachable();
      }
      if(!valid) continue;

      auto d = dirs[i];
      // std::cout << "position: " << pos.first+d[0] << ", " << pos.second+d[1] << "\n";
      if (pos.first+d[0] < 0 || pos.second+d[1] < 0) {
        continue;
      }
      auto look = grid[pos.first+d[0]][pos.second+d[1]];
      // std::cout << "Examining " << look << "\n";
      if(!is_visited(pos, direction, visited)) {
        switch (look) {
        case '|':
          if(direction == NORTH || direction == SOUTH) {
            pos = move_direction(pos, direction);
            // std::cout << "choosing | by going " << direction_to_string(i) << "\n";
            next = true;
          }
          break;
        case '-':
          if(direction == EAST || direction == WEST) {
            pos = move_direction(pos, direction);
            next = true;
            // std::cout << "choosing - by going " << direction_to_string(i) << "\n";
          }
          break;
        case 'L':
          if(direction == SOUTH || direction == WEST) {
            pos = move_direction(pos, direction);
            next = true;
            // std::cout << "choosing L by going " << direction_to_string(i) << "\n";
          }
          break;
        case 'F':
          if(direction == NORTH || direction == WEST) {
            pos = move_direction(pos, direction);
            next = true;
            // std::cout << "choosing F by going " << direction_to_string(i) << "\n";
          }
          break;
        case 'J':
          if(direction == EAST || direction == SOUTH) {
            pos = move_direction(pos, direction);
            next = true;
            // std::cout << "choosing J by going " << direction_to_string(i) << "\n";
          }
          break;
        case '7':
          if(direction == EAST || direction == NORTH) {
            pos = move_direction(pos, direction);
            next = true;
            // std::cout << "choosing 7 by going " << direction_to_string(i) << "\n";
          }
          break;
        case '.':
          break;
        case 'S':
          break;
        default:
          std::unreachable();
        }
      }
      if(next == true){
        moves += 1;
        break;
      }
    }

    if(next == false) {
      break;
    }
    if (pos == start) {
      break;
    }
  }
  auto part1 = moves / 2 + 1;



  /* PART 2=============================== */

  std::vector<std::vector<char>> highres_grid = multiply_graph(grid, 3);
  std::vector<std::vector<bool>> highres_loop = multiply_visited(visited, 3);

  std::cout << "regular grid\n==============\n";
  for(int i = 0; i < grid.size(); ++i) {
    for(int j = 0; j < grid[0].size(); ++j) {
      std::cout << grid[i][j];
    }
    std::cout << "\n";
  }
  std::cout << "high res grid\n==============\n";
  for(int i = 0; i < highres_grid.size(); ++i) {
    for(int j = 0; j < highres_grid[0].size(); ++j) {
      std::cout << highres_grid[i][j];
    }
    std::cout << "\n";
  }
  std::cout << "high res loop\n==============\n";
  for(int i = 0; i < highres_loop.size(); ++i) {
    for(int j = 0; j < highres_loop[0].size(); ++j) {
      std::cout << highres_loop[i][j];
    }
    std::cout << "\n";
  }

  
  std::vector<std::vector<bool>> highres_visited = multiply_visited(visited, 3);
  for(int i = 0; i < highres_visited.size(); ++i) {
    for(int j = 0; j < highres_visited[0].size(); ++j) {
      highres_visited[i][j] =  false;
    }
  }

  std::queue<std::pair<int64_t, int64_t>> q;
  q.push({1, 1});

  while(!q.empty()) {
    auto [y, x] = q.front();
    q.pop();

    for(auto d: dirs) {
      auto nx = x + d[0];
      auto ny = y + d[1];

      if(ny < highres_grid.size() && nx >= 0 && nx < highres_grid[0].size() && ny >= 0) {
        if(highres_grid[ny][nx] == '.') {
          // std::cout << "pushing: " << ny << ", " << nx << "\n";
          q.push({ny, nx});
          highres_grid[ny][nx] = 'O';
        }
      }
    // for(int i = 0; i < highres_grid.size(); ++i) {
    //   for(int j = 0; j < highres_grid[0].size(); ++j) {
    //     std::cout << highres_grid[i][j];
    //   }
    //   std::cout << "\n";
    // }
    }
  }
  
  std::cout << "regular grid\n==============\n";
  for(int i = 0; i < grid.size(); ++i) {
    for(int j = 0; j < grid[0].size(); ++j) {
      std::cout << grid[i][j];
    }
    std::cout << "\n";
  }

  std::cout << "visited grid\n==============\n";
  for(int i = 0; i < visited.size(); ++i) {
    for(int j = 0; j < visited[0].size(); ++j) {
      std::cout << visited[i][j];
    }
    std::cout << "\n";
  }

  std::vector<std::vector<bool>> last_visits(grid.size(), std::vector<bool>(grid[0].size()));
  for(auto v: last_visits) {
    std::fill(v.begin(),  v.end(), false);
  }

  auto tiles = 0;
  bool inside = 0;

  for(int i = 0; i < grid.size(); ++i) {
    for(int j = 0; j < grid[0].size(); ++j) {

    }
  }

  std::cout << "Flood Filled low res grid\n==============\n";
  for(int i = 0; i < grid.size(); ++i) {
    for(int j = 0; j < grid[0].size(); ++j) {
      if(highres_grid[(i*3)][(j*3)] != 'O' && visited[i][j] == false) {
        q.push({i, j});
        while(!q.empty()) {
          auto [y, x] = q.front();
          last_visits[x][y] = true;
          q.pop();

          for(auto d: dirs) {
            auto ny = y + d[1];
            auto nx = x + d[0];

            if(ny < highres_grid.size() && nx >= 0 && nx < highres_grid[0].size() && ny >= 0) {
              if(last_visits[ny][nx] == false && grid[ny][nx] != 'O') {
                last_visits[ny][nx] = true;
                q.push({ny, nx});
              } else if (visited[ny][nx] == true) {
                goto found;
              }
            }
          }
        }


found:
        grid_edit[i][j] = 'I';
        tiles++;
      }
      std::cout << grid_edit[i][j];
    }
    std::cout << "\n";
  }


  std::cout << "Flood Filled high res grid\n==============\n";
  for(int i = 0; i < highres_grid.size(); ++i) {
    for(int j = 0; j < highres_grid[0].size(); ++j) {
      std::cout << highres_grid[i][j];
    }
    std::cout << "\n";
  }
  std::cout << "tiles: " << tiles << "\n";

  return part1;
}

int main() {

  auto content = get_file_as_string("../data.txt");
  // printf("%lld\n", part1(".....\n.S-7.\n.|.|.\n.L-J.\n....."));
  // printf("%lld\n", part1("..F7.\n.FJ|.\nSJ.L7\n|F--J\nLJ..."));
  printf("%lld\n", part1(content));
  // printf("%lld\n", part1("...........\n.S-------7.\n.|F-----7|.\n.||.....||.\n.||.....||.\n.|L-7.F-J|.\n.|..|.|..|.\n.L--J.L--J.\n..........."));
  // printf("%lld\n", part1("FF7FSF7F7F7F7F7F---7\nL|LJ||||||||||||F--J\nFL-7LJLJ||||||LJL-77\nF--JF--7||LJLJ7F7FJ-\nL---JF-JLJ.||-FJLJJ7\n|F|F-JF---7F7-L7L|7|\n|FFJF7L7F-JF7|JL---7\n7-L-JL7||F7|L7F-7F7|\nL.L7LFJ|||||FJL7||LJ\nL7JLJL-JLJLJL--JLJ.L"));
  // printf("%lld\n", part1("..........\n.S------7.\n.|F----7|.\n.||....||.\n.||....||.\n.|L-7F-J|.\n.|..||..|.\n.L--JL--J.\n.........."));
  // printf("%lld\n", part1(".F----7F7F7F7F-7....\n.|F--7||||||||FJ....\n.||.FJ||||||||L7....\nFJL7L7LJLJ||LJ.L-7..\nL--J.L7...LJS7F-7L7.\n....F-J..F7FJ|L7L7L7\n....L7.F7||L7|.L7L7|\n.....|FJLJ|FJ|F7|.LJ\n....FJL-7.||.||||...\n....L---J.LJ.LJLJ..."));
  return 0;
}
