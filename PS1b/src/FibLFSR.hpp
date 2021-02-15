#ifndef _FIBLFSR_HPP
#define _FIBLFSR_HPP 1

#include <cstddef>
#include <iostream>
#include <set>
#include <string>
#include <vector>

// Class declaration of the LFSR implementation.
class FibLFSR
{
  public:
    // Constructor for FibLFSR. seed must be a string of 1's and 0's, and
    // tap_values are a set of indices within the range of seed's length.
    FibLFSR(std::string seed, std::set<unsigned> tap_values);

    // Constructor for FibLFSR. Uses a hash function to create a 64-bit-long
    // register from the keyphrase, with tap positions using the Fibonacci sequence.
    FibLFSR(std::string keyphrase);

    // Performs one shift step in the LFSR. Returns the inserted bit.
    int step();

    // Performs k shift steps in the LFSR and returns the k bits inserted
    // as an integer.
    int generate(int k);

    friend std::ostream &operator<<(std::ostream &out, FibLFSR &L);

  private:
    // Return the set of Fibonacci sequence up to n, exclusive.
    static std::set<unsigned> FibonacciValues(unsigned n);

    const unsigned _HASH_CONST = 41849243;
    const unsigned _HASH_MULT = 33;

    unsigned long long _register; // Internal container for the register
    std::set<unsigned> _taps;    // Set of tap indices
    
    const size_t _MAX_SIZE = 64;
    size_t N;
};

#endif // End of FibLFSR.hpp