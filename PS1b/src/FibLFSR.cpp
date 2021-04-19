// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include "FibLFSR.hpp"

#include <cstddef>
#include <stdexcept>

FibLFSR::FibLFSR(std::string seed, std::set<unsigned> tap_values)
    : register_(0), N(seed.size()) {
  if (N == 0) throw std::invalid_argument("Given seed is empty.");

  if (N >= MAX_SIZE) {
    std::cerr << "Warning: given seed \"" << seed
              << "\" is too long, only evaluating the first "
              << MAX_SIZE << " bits.\n";
    N = MAX_SIZE;
  }

  for (unsigned i = 0; i < N; i++) {
    int c = seed[N - 1 - i] - '0';
    if (c == 1)
      register_ |= 1LLU << i;
    else if (c != 0)
      throw std::invalid_argument("Invalid characters in seed.");
  }

  taps = tap_values.empty() ? FibonacciValues(N) : tap_values;
  taps.insert(N - 1);      // Add the leftmost index as a tap
  if (*taps.rbegin() > N)  // if shorter than largest tap -> exception
    throw std::invalid_argument("Tap index out-of-bounds.");
}

FibLFSR::FibLFSR(std::string keyphrase) {
  if (keyphrase.length() == 0)
    throw std::invalid_argument("Given keyphrase is empty.");
  // Hashes a keyphrase to a 64-bit long seed for the register.
  size_t hash = HASH_CONST;
  for (auto c : keyphrase) hash = HASH_MULT * hash + c;

  N = 64;
  register_ = hash;
  taps = FibonacciValues(N);
}

int FibLFSR::step() {
  bool feedback_bit = 0;
  for (unsigned i : taps) feedback_bit ^= (register_ & (1LLU << i)) && true;
  register_ <<= 1;
  register_ |= feedback_bit;
  return feedback_bit;
}

int FibLFSR::generate(int k) {
  int feedback_value = 0;
  while (--k >= 0) feedback_value = step() + (feedback_value << 1);
  return feedback_value;
}

std::ostream &operator<<(std::ostream &out, FibLFSR &L) {
  std::string result;
  for (unsigned i = 0; i < L.N; i++)
    result += '0' + ((L.register_ & (1LLU << i)) && true);
  return out << result;
}

std::set<unsigned> FibLFSR::FibonacciValues(unsigned n) {
  std::set<unsigned> list{1};
  if (n <= 2) return list;

  unsigned next_val = 2;
  do {
    list.insert(next_val);
    // Note that list is std::set<unsigned>, so `.rbegin()` retrieves the
    // largest element in the set.
    next_val = *list.rbegin() + *(--list.rbegin());
  } while (next_val < n);

  return list;
}
