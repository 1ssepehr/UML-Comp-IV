// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include "StringSound.hpp"
#include "CircularBuffer.hpp"

StringSound::StringSound(double frequency) {
  if (frequency <= 0) {
    throw std::invalid_argument("Frequency must be greater than zero");
  } else {
    int capacity = 44100.0 / frequency;
    buffer = std::make_unique<CircularBuffer<std::int16_t>>(capacity);
    for (int i = 0; i < capacity; i++) {
      buffer->enqueue((int16_t)0);
    }
    time_ = 0;
  }
}

StringSound::StringSound(std::vector<std::int16_t> init) {
  if (init.size() <= 0) {
    throw std::invalid_argument("Initial value must be greater than zero");
  } else {
    buffer = std::make_unique<CircularBuffer<std::int16_t>>(init.size());
    for (unsigned i = 0; i < init.size(); i++) {
      buffer->enqueue(init.at(i));
    }
    time_ = 0;
  }
}

void StringSound::pluck() {
  while (!(*buffer).isEmpty()) {
    buffer->dequeue();
  }
  while (!(*buffer).isFull()) {
    buffer->enqueue((std::int16_t)(rand() & 0xffff));
  }
}

void StringSound::tic() {
  int16_t value1 = buffer->dequeue();
  int16_t value2 = buffer->peek();
  int16_t total = (value1 + value2) / 2;
  int16_t temp = total * buffer->DECAY_FACTOR;
  buffer->enqueue(temp);
  time_++;
}

std::int16_t StringSound::sample() { return buffer->peek(); }

size_t StringSound::time() { return time_; }