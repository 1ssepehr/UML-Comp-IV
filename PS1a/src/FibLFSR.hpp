// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#ifndef PS1A_SRC_FIBLFSR_HPP_
#define PS1A_SRC_FIBLFSR_HPP_ 1

#include <iostream>
#include <set>
#include <string>
#include <vector>

class FibLFSR {
 public:
  FibLFSR(std::string seed, std::set<unsigned> tap_values);
  int step();
  int generate(int k);
  friend std::ostream& operator<<(std::ostream& out, FibLFSR X);

 private:
  std::vector<bool> reg_list;
  std::set<unsigned> taps;
  unsigned N;
};

#endif  // PS1A_SRC_FIBLFSR_HPP_
