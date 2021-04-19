# PS4a: CircularBuffer implementation with unit tests and exceptions [README-PS4a.md]

***Name:** Seyedsepehr Madani*

***Hours to complete assignment:** 2 hours*

---

## Questions

**Briefly discuss the assignment itself and waht you accomplished.**

In this assignment, we provide an implementation of a circular buffer. This is a buffer of a fixed capacity which allows for insertion at the end, and deletion from the front (with `enqueue()` and `dequeue()`).

For my implementation, I used a dynamically-allocated array using `std::unique_ptr<T>()` with template numerical type `T` for the buffer.

Assignment directory:

```text
PS4a
├── src
│   └─── CircularBuffer.cpp CircularBuffer.hpp test.cpp
├── README-PS4a.md/pdf (this file)
└── Makefile
```

The program can be run via:

```Bash
make all && ./PS4a --log_level=all
```

---

**Discuss one or more key algorithms, data structures, or Object-Oriented designs that were central to the assignment.**

It might sound appealing to use STL containers for implementing a circular buffer, but I thought that making a simple buffer of my own with a dynamic array would make the program smaller and faster than something like `std::vector` or `std::deque`.

The key observation here was that the *capacity of the buffer is fixed*. That means the extensibility of STL containers are not necessary; in fact, if we use them, we would have to limit them to a fixed capacity. That did not seem like an ideal design to me.

---

**Briefly explain the workings of the features you implemented. Include code excerpts.**

Internally, I keep track of the beginning and the end of the buffer via private members `size_t front, back`.
Each `enqueue()` or `dequeue()` increments `back` or `front` respectively, calculating them modulo `capacity`, hence *circularly*).

My `enqueue()` example is shown below.

```c++
template <typename T>
void CircularBuffer<T>::enqueue(T x) {
  if (isFull())
    throw std::runtime_error("enqueue: can't enqueue to a full ring.");
  buffer[back] = x;
  back = (back + 1) % capacity;
  ++used_size;
}
```

The number of items in the buffer is also tracked by private member `size_t used_size`. This makes the implementation of `isFull()` and `isEmpty()` trivial, as shown below.

```c++
bool isEmpty() const { return used_size == 0; }
bool isFull() const { return used_size == capacity; }
```

---

**Did you complete the whole assignment? Successfully or not? Indicate which parts you think are working, and describe how you know that they're working.**

Yes, all of PS4a is completed (including _cpplint_). I also made the `CircularBuffer` class a template class for versatility (and programming practice!). The test unit, Makefile, and the code all work properly. I also formatted my code using `clang-format` with Google's coding style.

---

**Does your CircularBuffer implementation pass the unit tests? Indicate yes or no, and explain how you know that it does or does not.**

Yes, the implementation passes the unit tests.

I was looking for two main elements to be checked in the unit tests:

1. The "circularity" of the buffer; that is, making sure that repeated `enqueue()` and `dequeue()` operations would safely flow the data inside the buffer, with no errors.

2. Exception safety. That includes overflow, bad arguments, `dequeue()` on empty buffer.

Both items are explicitly tested using Boost's Unit Testing framework.

---

**Explain the time and space performance of your RingBuffer implementation.**

This implementation uses `O(N)` space and `O(1)` time for `enqueue()`, `dequeue()`, and `peek()`.

---

**List whatever help (if any) you received from the instructor, classmates, or anyone else.**

I did this assignment on my own.

---

**Describe any serious problems you encountered.**

I had no problems during this assignment.

---

**List any other comments here.**
