// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#ifndef PS6_SRC_INTOUCH_BOOT_HPP_
#define PS6_SRC_INTOUCH_BOOT_HPP_

#include <boost/regex.hpp>

static const boost::regex boot_start("\\(log\\.c\\.166\\) server started");
static const boost::regex boot_end(
    "oejs\\.AbstractConnector:Started SelectChannelConnector");
static const boost::regex boot_finish("");

#endif  // PS6_SRC_INTOUCH_BOOT_HPP_
