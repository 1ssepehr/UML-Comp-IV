// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#ifndef PS1B_SRC_FIBLFSR_HPP_
#define PS1B_SRC_FIBLFSR_HPP_ 1

#include <cstdint>
#include <cstddef>
#include <iostream>
#include <set>
#include <string>

// Class declaration of the LFSR implementation.
class FibLFSR {
 public:
  // Constructor for FibLFSR. seed must be a string of 1's and 0's, and
  // tap_values are a set of indices within the range of seed's length.
  FibLFSR(std::string seed, std::set<unsigned> tap_values);

  // Constructor for FibLFSR. Uses a hash function to create a 64-bit-long
  // register from the keyphrase, with tap positions using the Fibonacci
  // sequence.
  explicit FibLFSR(std::string keyphrase);

  // Performs one shift step in the LFSR. Returns the inserted bit.
  int step();

  // Performs k shift steps in the LFSR and returns the k bits inserted
  // as an integer.
  int generate(int k);

  friend std::ostream &operator<<(std::ostream &out, FibLFSR &L);

 private:
  // Return the set of Fibonacci sequence up to n, exclusive.
  static std::set<unsigned> FibonacciValues(unsigned n);

  static constexpr unsigned HASH_CONST = 41849243;
  static constexpr unsigned HASH_MULT = 33;
  static constexpr size_t MAX_SIZE = 64;

  std::int64_t register_;   // Internal container for the register
  std::set<unsigned> taps;  // Set of tap indices

  size_t N;
};

#endif  // PS1B_SRC_FIBLFSR_HPP_
