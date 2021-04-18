// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/regex.hpp>

#include "kronos.hpp"

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    std::cerr << "Missing file argument." << std::endl;
  }

  std::string log_path{argv[1]};

  std::ifstream log_file(log_path);
  std::ofstream output(log_path + ".rpt");

  if (log_file.is_open() == false) {
    std::cerr << "error: cannot open specified file " << log_path << std::endl;
    return (-1);
  }

  bool liveDevice = false;  // Boot completion flag
  bool complete = false;
  std::string line;         // Line string image
  size_t line_number = 0;   // Line number flag

  boost::gregorian::date startDate, endDate;
  boost::posix_time::ptime startTime, endTime;

  // Read lines from log (+ keep track of line numbers)
  while (++line_number, std::getline(log_file, line)) {
    // Boot starting sequence
    boost::smatch what_start;
    if (boost::regex_search(line, what_start, boot_start) == true) {
      startDate = boost::gregorian::from_simple_string(line.substr(0, 10));
      startTime = boost::posix_time::time_from_string(line.substr(11, 8));

      if (complete == false) {
        output << "**** Incomplete boot ****\n" << std::endl;
        output << "=== Device boot ===\n"
               << line_number << "(" << log_path << "): " << line.substr(0, 19)
               << " Boot Start" << std::endl;
      }
    }

    // Boot ending sequence
    boost::smatch what_end;
    if (boost::regex_search(line, what_end, boot_end)) {
      endDate = boost::gregorian::from_simple_string(line.substr(0, 10));
      endTime = boost::posix_time::time_from_string(line.substr(11, 8));

      output << line_number << "(" << log_path << "): " << line.substr(0, 19)
             << " Boot Completed" << std::endl;

      boost::posix_time::time_duration td = startTime - endTime;
      output << "\tBoot Time: " << td.total_milliseconds() << "ms\n"
             << std::endl;
      complete = true;
    }
  }

  output.close();
  log_file.close();
  return 0;
}
