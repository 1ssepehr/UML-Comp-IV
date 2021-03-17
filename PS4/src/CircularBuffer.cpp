#include "CircularBuffer.hpp"

#include <cstddef>
#include <cstdint>
#include <exception>
#include <memory>
#include <stdexcept>

CircularBuffer::CircularBuffer(size_t capacity) : capacity(capacity), used_size(0), front(0), back(0)
{
    if (capacity < 1)
        throw std::invalid_argument("CircularBuffer constructor: capacity must be greater than zero.");
    buffer = std::make_unique<std::int16_t[]>(capacity);
}

void CircularBuffer::enqueue(std::int16_t x)
{
    if (isFull())
        throw std::runtime_error("enqueue: can't enqueue to a full ring.");
    buffer[back] = x;
    if (++back >= capacity)
        back = 0;
    ++used_size;
}

std::int16_t CircularBuffer::dequeue()
{
    if (isEmpty())
        throw std::runtime_error("dequeue: can't dequeue an empty ring.");
    auto value = buffer[front];
    ++front;
    --used_size;
    return value;
}

std::int16_t CircularBuffer::peek()
{
    return buffer[front];
}