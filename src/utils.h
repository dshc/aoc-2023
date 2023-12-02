#ifndef UTILS
#define UTILS

#include <string>
#include <utility>

namespace utils {

// trim from start (in place)
inline void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
          }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) { return !std::isspace(ch); })
              .base(),
          s.end());
}

// trim from both ends (in place)
inline void trim(std::string &s) {
  rtrim(s);
  ltrim(s);
}

inline std::pair<std::string, std::string>
splitAndMakePair(const std::string &str, char delim = ' ') {
  auto index = str.find(delim);
  return std::make_pair(str.substr(0, index), str.substr(index + 1));
}

} // namespace utils

#endif
