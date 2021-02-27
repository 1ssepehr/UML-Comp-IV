#include "Universe.hpp"
#include "CelestialBody.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    Universe SolarSystem;
    std::cin >> SolarSystem;
    SolarSystem.setTitle("Solar System");
    SolarSystem.load();
    return 0;
}