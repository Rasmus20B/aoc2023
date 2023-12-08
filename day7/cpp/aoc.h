#include <vector>
#include <string>
#include <string_view>
#include <sstream>
#include <concepts>
#include <fstream>


std::string get_file_as_string(const std::string_view filename) {
  std::ifstream in;
  in.open(filename);
  std::stringstream out;
  out << in.rdbuf();
  return out.str();
}

template<typename T>
requires(std::is_convertible_v<T, std::string_view>)
std::vector<T> split(const std::string& str, const std::string& delim) {
  std::vector<T> strings;

  std::string::size_type pos = 0;
  std::string::size_type prev = 0;

  while((pos = str.find(delim.data(), prev)) != std::string::npos) {
    strings.push_back((str.substr(prev, pos - prev).data()));
    prev = pos + delim.size();
  }
  strings.push_back((str.substr(prev).data()));

  return strings;
}

template<typename T>
requires(std::is_integral_v<T> || std::is_floating_point_v<T>)
std::vector<T> split(const std::string& str, const std::string& delim) {
  std::vector<T> strings;

  std::string::size_type pos = 0;
  std::string::size_type prev = 0;

  while((pos = str.find(delim.data(), prev)) != std::string::npos) {
    std::string s = str.substr(prev, pos - prev).data();
    if(s != "") {
      strings.push_back(std::stoi(s));
    }
    prev = pos + delim.size();
  }
  std::string s = str.substr(prev, pos - prev).data();
  if(s != "") {
    strings.push_back(std::stoi(s));
  }
  prev = pos + delim.size();

  return strings;
}
