// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include <iostream>

#include "CelestialBody.hpp"
#include "Universe.hpp"

int main(int argc, char *argv[]) {
  Universe SolarSystem;
  std::cin >> SolarSystem;
  SolarSystem.setTitle("Solar System");
  SolarSystem.load();
  return 0;
}
