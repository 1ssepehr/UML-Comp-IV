// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#ifndef PS3_SRC_ED_HPP_
#define PS3_SRC_ED_HPP_

#include <cstdint>
#include <memory>
#include <string>
#include <utility>

typedef std::int16_t cell;

class ED {
 public:
  ED(const std::string A, const std::string B);
  ED(const ED &other) = delete;
  ED &operator=(const ED &other) = delete;

  int OptDistance();
  std::string Alignment();

 private:
  std::unique_ptr<std::unique_ptr<cell[]>[]> M;
  std::string A;
  std::string B;
  constexpr static cell MATCH = 0;
  constexpr static cell MISMATCH = 1;
  constexpr static cell GAP = 2;

  constexpr static cell penalty(char a, char b) {
    return (a == b) ? MATCH : MISMATCH;
  }

  constexpr static cell min3(cell a, cell b, cell c) {
    if (a <= b && a <= c) return a;
    return (b <= c) ? b : c;
  }
};

#endif  // PS3_SRC_ED_HPP_
