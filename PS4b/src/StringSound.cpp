// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include "StringSound.hpp"

#include <cmath>
#include <cstddef>
#include <random>

#include "CircularBuffer.hpp"
#include "Guitar.hpp"

constexpr static auto seed = 239174213U;
static std::uniform_int_distribution<uint32_t>
    rand_dist;                 // For random generation
static std::mt19937 MT(seed);  // The Mersenne Twister

StringSound::StringSound(double frequency) : ticCount(0) {
  if (frequency <= 0) {
    throw std::invalid_argument("Frequency must be greater than zero");
  } else {
    auto capacity =
        static_cast<std::size_t>(std::ceil(SAMPLES_PER_SEC / frequency));
    buffer = std::make_unique<CircularBuffer<std::int16_t>>(capacity);
  }
}

StringSound::StringSound(const std::vector<std::int16_t> &init) : ticCount(0) {
  if (init.size() <= 0) {
    throw std::invalid_argument("Initial value must be greater than zero");
  } else {
    buffer = std::make_unique<CircularBuffer<std::int16_t>>(init.size());
    for (auto x : init) buffer->enqueue(x);
  }
}

void StringSound::pluck() {
  buffer->reset();
  while (buffer->isFull() == false) buffer->enqueue(rand_dist(MT));
}

void StringSound::tic() {
  auto x1 = buffer->dequeue();
  auto x2 = buffer->peek();
  std::int16_t next = 0.5 * (x1 + x2) * buffer->DECAY_FACTOR;
  buffer->enqueue(next);
  ticCount++;
}

std::int16_t StringSound::sample() { return buffer->peek(); }

size_t StringSound::getTicCount() { return ticCount; }
