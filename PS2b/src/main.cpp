// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "CelestialBody.hpp"
#include "Universe.hpp"

int main(int argc, char *argv[]) {
  if (argc < 3)
    throw std::invalid_argument("Missing arguments for time information.");
  auto T = std::atof(argv[1]);
  auto delta_T = std::atof(argv[2]);

  Universe SolarSystem(T, delta_T);
  std::cin >> SolarSystem;
  SolarSystem.setTitle("Universe (With Runge Kutta)");
  SolarSystem.load();
  std::cout << SolarSystem;
  return 0;
}
