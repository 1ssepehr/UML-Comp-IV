// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#ifndef STRINGSOUND_HPP_
#define STRINGSOUND_HPP_

#include <memory>
#include <vector>
#include <cstdint>
#include "CircularBuffer.hpp"

class StringSound {
 public:
  explicit StringSound(double frequency);
  explicit StringSound(std::vector<std::int16_t> init);
  StringSound(const StringSound &other) = delete;

  void pluck();

  void tic();

  std::int16_t sample();

  size_t time();
 private:
  std::unique_ptr<CircularBuffer<std::int16_t>> buffer;
  size_t time_;
};

#endif  // STRINGSOUND_HPP_