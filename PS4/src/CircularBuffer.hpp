// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#ifndef PS4_SRC_CIRCULARBUFFER_HPP_
#define PS4_SRC_CIRCULARBUFFER_HPP_ 1

#include <cstddef>
#include <cstdint>
#include <memory>

class CircularBuffer {
 public:
  explicit CircularBuffer(size_t capacity);
  CircularBuffer() : CircularBuffer(16) {}

  ~CircularBuffer() = default;

  CircularBuffer(const CircularBuffer &other) = delete;
  CircularBuffer(CircularBuffer &&other) = delete;

  CircularBuffer &operator=(const CircularBuffer &other) = delete;
  CircularBuffer &operator=(const CircularBuffer &&other) = delete;

  size_t size() const { return used_size; }
  bool isEmpty() const { return used_size == 0; }
  bool isFull() const { return used_size == capacity; }
  void enqueue(std::int16_t x);
  std::int16_t dequeue();
  std::int16_t peek();

 private:
  std::unique_ptr<std::int16_t[]> buffer;
  size_t front;      // Index of the first element
  size_t back;       // Index after the last used element
  size_t used_size;  // Number of elements in use
  size_t capacity;   // Total capacity of the buffer

  constexpr static double DECAY_FACTOR = 0.996;
};

#endif  // PS4_SRC_CIRCULARBUFFER_HPP_
