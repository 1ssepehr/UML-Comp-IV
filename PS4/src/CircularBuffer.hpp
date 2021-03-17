#ifndef CIRCULAR_BUFFER_HPP
#define CIRCULAR_BUFFER_HPP 1

#include <cstddef>
#include <cstdint>
#include <memory>

class CircularBuffer
{
  public:
    CircularBuffer(size_t capacity);
    CircularBuffer() : CircularBuffer(16)
    {
    }

    ~CircularBuffer() = default;

    CircularBuffer(CircularBuffer &other) = delete;
    CircularBuffer(CircularBuffer &&other) = delete;

    CircularBuffer &operator=(const CircularBuffer &other) = delete;
    CircularBuffer &operator=(const CircularBuffer &&other) = delete;

    size_t size() const
    {
        return used_size;
    }
    bool isEmpty() const
    {
        return used_size == 0;
    }
    bool isFull() const
    {
        return used_size == capacity;
    }
    void enqueue(std::int16_t x);
    std::int16_t dequeue();
    std::int16_t peek();

  private:
    std::unique_ptr<std::int16_t[]> buffer;
    int front;     // Index to the first element
    int back;      // Index of the right of the last element (first free cell, if any)
    size_t used_size; // Number of elements in use
    size_t capacity;  // Total capacity of the buffer

    constexpr static double DECAY_FACTOR = 0.996;
};

#endif