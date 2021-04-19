// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main

#include <stdexcept>
#include <boost/test/unit_test.hpp>

#include "../src/FibLFSR.hpp"

#define CHEATOFORME(X) std::cout << (X) << std::endl

// Testing a 16-bit LFSR with initial seed "1011011000110110" and tap positions
// 10, 12, 13
BOOST_AUTO_TEST_CASE(binarySeedTest) {
  FibLFSR l1("1011011000110110", {10, 12, 13});
  BOOST_REQUIRE(l1.step() == 0);
  BOOST_REQUIRE(l1.step() == 0);
  BOOST_REQUIRE(l1.step() == 0);
  BOOST_REQUIRE(l1.step() == 1);
  BOOST_REQUIRE(l1.step() == 1);
  BOOST_REQUIRE(l1.step() == 0);
  BOOST_REQUIRE(l1.step() == 0);
  BOOST_REQUIRE(l1.step() == 1);

  FibLFSR l2("1011011000110110", {10, 12, 13});
  BOOST_REQUIRE(l2.generate(9) == 51);
}

// Testing an [64-bit] LFSR with initial keyphrase "5NotoriousBlueberries"
BOOST_AUTO_TEST_CASE(keyphraseTest) {
  FibLFSR l1("5NotoriousBlueberries");

  BOOST_REQUIRE(l1.step() == 0);
  BOOST_REQUIRE(l1.step() == 0);
  BOOST_REQUIRE(l1.step() == 1);
  BOOST_REQUIRE(l1.step() == 0);
  BOOST_REQUIRE(l1.step() == 0);
  BOOST_REQUIRE(l1.step() == 0);
  BOOST_REQUIRE(l1.step() == 0);
  BOOST_REQUIRE(l1.step() == 1);
  BOOST_REQUIRE(l1.step() == 1);

  FibLFSR l2("5NotoriousBlueberries");
  BOOST_REQUIRE(l2.generate(16) == 8613);
}

// test exception-safety of the FibLFSR moduole
BOOST_AUTO_TEST_CASE(exceptionSafety) {
  BOOST_REQUIRE_THROW(FibLFSR l1("", {}), std::invalid_argument);
  BOOST_REQUIRE_THROW(FibLFSR l1("100100110", {5, 10}), std::invalid_argument);
  BOOST_REQUIRE_THROW(FibLFSR l1("31646484796", {2, 5}), std::invalid_argument);
  BOOST_REQUIRE_THROW(FibLFSR l1(""), std::invalid_argument);
}
