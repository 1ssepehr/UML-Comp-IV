// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#ifndef PS4B_SRC_STRINGSOUND_HPP_
#define PS4B_SRC_STRINGSOUND_HPP_

#include <cstdint>
#include <memory>
#include <vector>

#include "CircularBuffer.hpp"

class StringSound {
 public:
  // Create a guitar string sound of the given frequency using a sampling rate
  // of 44,100.
  explicit StringSound(double frequency);

  // Create a guitar string with size and initial values are given by the
  // vector.
  explicit StringSound(const std::vector<std::int16_t> &init);

  StringSound(const StringSound &other) = delete;

  // pluck the guitar string by replacing the buffer with random values,
  // representing white noise
  void pluck();

  // Advance the simulation one time step.
  void tic();

  // Return the current sample
  std::int16_t sample();

  // return number of times tic() was called so far
  size_t getTicCount();

 private:
  std::unique_ptr<CircularBuffer<std::int16_t>> buffer;
  size_t ticCount;
};

#endif  // PS4B_SRC_STRINGSOUND_HPP_
