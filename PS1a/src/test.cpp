// Dr. Rykalova
// test.cpp for PS1a
// updated 1/31/2020
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main

#include "FibLFSR.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(sixteenBitsThreeTaps)
{
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

// testing an 8-bit LFSR with initial seed 00010010 and tap position 2, 7
BOOST_AUTO_TEST_CASE(eightBitsTwoTap) {
    FibLFSR l1("00010010", {2, 7});
    BOOST_REQUIRE(l1.step() == 0);
    BOOST_REQUIRE(l1.step() == 1);
    BOOST_REQUIRE(l1.step() == 0);
    BOOST_REQUIRE(l1.step() == 1);
    BOOST_REQUIRE(l1.step() == 1);
    BOOST_REQUIRE(l1.step() == 0);
    BOOST_REQUIRE(l1.step() == 0);
    BOOST_REQUIRE(l1.step() == 1);
    BOOST_REQUIRE(l1.step() == 0);
    FibLFSR l2("00010010", {2, 7});
    BOOST_REQUIRE(l2.generate(11) == 715);
}

// test exception-safety of the FibLFSR moduole
BOOST_AUTO_TEST_CASE(exceptionSafety) {
    try
    {
        FibLFSR l1("", {});
        BOOST_ERROR("Empty seed string exception not caught");
    } catch (std::invalid_argument &e) {}
    
    try
    {
        FibLFSR l1("100100110", {5, 10});
        BOOST_ERROR("Out-of-bounds tap index exception not caught");
    } catch (std::invalid_argument &e) {}

    try
    {
        FibLFSR l1("31646484796", {2, 5});
        BOOST_ERROR("Invalid characters in seed string exception not caught");
    } catch (std::invalid_argument &e) {}
}
