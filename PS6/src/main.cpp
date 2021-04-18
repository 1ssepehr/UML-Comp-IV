// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/regex.hpp>

#include "intouch_boot.hpp"

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    std::cerr << "Missing file argument." << std::endl;
  }

  std::string pathname{argv[1]};

  std::ifstream log_file(pathname);
  std::ofstream output(pathname + ".rpt");
  std::stringstream report;

  if (log_file.is_open() == false) {
    std::cerr << "error: cannot open specified file " << pathname << std::endl;
    return (-1);
  }

  bool isBootInProcess = false;  // Boot completion flag

  std::string line;        // Line string image
  size_t line_number = 0;  // Line number flag

  size_t success = 0;  // Number of successful booting attempts
  size_t fail = 0;     // Number of successfulfailed booting attempts

  // Lambda expression to extract the timestamp substring from log entries
  auto extract_time = [](std::string x) { return x.substr(0, 19); };

  // Read lines from log (+ keep track of line numbers)
  boost::posix_time::ptime startTime, endTime;
  while (std::getline(log_file, line)) {
    ++line_number;

    // Boot starting sequence
    if (boost::regex_search(line, boot_start) == true) {
      startTime = boost::posix_time::time_from_string(extract_time(line));

      if (isBootInProcess == true) {
        report << "**** Incomplete boot ****\n\n";
        ++fail;
      }
      report << "=== Device boot ===\n"
             << line_number << "(" << pathname << "): " << extract_time(line)
             << " Boot Start\n";
      isBootInProcess = true;
    }

    // Boot ending sequence
    if (boost::regex_search(line, boot_end)) {
      endTime = boost::posix_time::time_from_string(extract_time(line));
      auto elapsedBootTime = endTime - startTime;

      ++success;
      isBootInProcess = false;

      report << line_number << "(" << pathname << "): " << extract_time(line)
             << " Boot Completed\n\tBoot Time: "
             << elapsedBootTime.total_milliseconds() << "ms\n\n";
    }
  }

  // Write the final report on the output file
  output << "Device Boot Report\n\n"
         << "InTouch log file: " << pathname << "\n"
         << "Lines Scanned: " << line_number << "\n\n"
         << "Device boot count: initiated = " << (success + fail)
         << ", completed = " << success << "\n\n\n"
         << report.rdbuf();

  output.close();
  log_file.close();
  return 0;
}
