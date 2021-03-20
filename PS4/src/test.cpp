// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE CircularBuffer_test

#include <stdexcept>
#include "CircularBuffer.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(enqueueDequeueTest) {
  CircularBuffer B(7);
  BOOST_REQUIRE(B.isEmpty());

  B.enqueue(9);
  B.enqueue(4);
  B.enqueue(1);
  B.enqueue(8);
  B.enqueue(3);

  BOOST_REQUIRE_EQUAL(B.dequeue(), 9);
  BOOST_REQUIRE_EQUAL(B.dequeue(), 4);
  BOOST_REQUIRE_EQUAL(B.dequeue(), 1);

  B.enqueue(7);
  B.enqueue(2);
  B.enqueue(0);
  B.enqueue(4);

  BOOST_REQUIRE_EQUAL(B.dequeue(), 8);
  BOOST_REQUIRE_EQUAL(B.dequeue(), 3);
  BOOST_REQUIRE_EQUAL(B.dequeue(), 7);

  BOOST_REQUIRE(!B.isFull());
  BOOST_REQUIRE(!B.isEmpty());
}

BOOST_AUTO_TEST_CASE(overflowTest) {
  CircularBuffer B(5);
  int16_t values[] = {8, 3, 6, 1, 10};
  for (auto x : values) B.enqueue(x);

  BOOST_REQUIRE(B.isFull());
  BOOST_REQUIRE_THROW(B.enqueue(0), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(emptyBufferDequeueTest) {
  CircularBuffer B(5);
  BOOST_REQUIRE_THROW(B.dequeue(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(badCapacityTest) {
  BOOST_REQUIRE_THROW(CircularBuffer B(0), std::invalid_argument);
}
