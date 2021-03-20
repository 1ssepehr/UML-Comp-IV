// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#ifndef PS4_SRC_CIRCULARBUFFER_HPP_
#define PS4_SRC_CIRCULARBUFFER_HPP_ 1

#include <cstddef>
#include <memory>
#include <stdexcept>

template <typename T>
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
  void enqueue(T x);
  T dequeue();
  T peek();

 private:
  std::unique_ptr<T[]> buffer;
  size_t front;      // Index of the first element
  size_t back;       // Index after the last used element
  size_t used_size;  // Number of elements in use
  size_t capacity;   // Total capacity of the buffer

  constexpr static double DECAY_FACTOR = 0.996;
};

template <typename T>
CircularBuffer<T>::CircularBuffer(size_t capacity)
    : capacity(capacity), used_size(0), front(0), back(0) {
  if (capacity < 1)
    throw std::invalid_argument(
        "CircularBuffer constructor: capacity must be greater than zero.");
  buffer = std::make_unique<T[]>(capacity);
}

template <typename T>
void CircularBuffer<T>::enqueue(T x) {
  if (isFull())
    throw std::runtime_error("enqueue: can't enqueue to a full ring.");
  buffer[back] = x;
  back = (back + 1) % capacity;
  ++used_size;
}

template <typename T>
T CircularBuffer<T>::dequeue() {
  if (isEmpty())
    throw std::runtime_error("dequeue: can't dequeue an empty ring.");
  auto value = buffer[front];
  front = (front + 1) % capacity;
  --used_size;
  return value;
}

template <typename T>
T CircularBuffer<T>::peek() {
  return buffer[front];
}

#endif  // PS4_SRC_CIRCULARBUFFER_HPP_
