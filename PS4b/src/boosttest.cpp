// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include <stdexcept>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE StringSoundUnitTest

#include "StringSound.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(ExceptionSafety) {
  // Test non-positive frequency for constructor
  BOOST_REQUIRE_THROW(StringSound SS(-1), std::invalid_argument);

  // Test empty std::vector for constructor
  BOOST_REQUIRE_THROW(StringSound SS({}), std::invalid_argument);
}
