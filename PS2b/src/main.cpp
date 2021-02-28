#include "Universe.hpp"
#include "CelestialBody.hpp"

#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
    auto T = std::atof(argv[1]);
    auto delta_T = std::atof(argv[2]);
    Universe SolarSystem(T, delta_T);

    std::cin >> SolarSystem;
    SolarSystem.setTitle("Solar System");
    SolarSystem.load();
    return 0;
}