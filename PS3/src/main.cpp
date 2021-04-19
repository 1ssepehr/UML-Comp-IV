// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include <chrono>  // NOLINT
#include <iostream>
#include <string>

#include "ED.hpp"

int main(int argc, char* argv[]) {
  std::string A, B;
  std::cin >> A >> B;
  ED ed(A, B);

  auto t_start = std::chrono::high_resolution_clock::now();

  auto dist = ed.OptDistance();
  auto alignment = ed.Alignment();

  auto t_end = std::chrono::high_resolution_clock::now();

  std::cout << "Edit distance = " << dist << "\n"
            << alignment << "\nElapsed time: "
            << std::chrono::duration<double>(t_end - t_start).count() << "s."
            << std::endl;
  return 0;
}
