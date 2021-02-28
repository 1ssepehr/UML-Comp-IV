#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <istream>
#include <memory>
#include <stdexcept>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "CelestialBody.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Universe : public sf::RenderWindow
{
  public:
    // Default constructor
    Universe() : N(0), R(DEFAULT_R), curTime(0), endTime(DEFAULT_TIME), delta_t(DEFAULT_DELTA_T)
    {
        loadArtifacts();
    }

    // Main constructor
    Universe(double endTime, double delta_t) : N(0), R(DEFAULT_R), curTime(0), endTime(endTime), delta_t(delta_t)
    {
        if (endTime <= 0)
            throw std::invalid_argument("Error: Given T (end time for Universe object) is negative.");
        loadArtifacts();
    }

    // Extraction operator for reading N, R from input stream
    friend std::istream &operator>>(std::istream &in, Universe &universe);

    // Loads the window of simulation
    void load();

    constexpr static auto G = 6.674e-11; // Gravitational Constant

  private:
    // Reads assets and initializes SFML artifacts for simulation based on N, R value
    void loadArtifacts();

    // Steps once through time (by delta_t) and moves the
    void step(double time);

    constexpr static auto DEFAULT_TITLE = "Universe";         // Default window title
    constexpr static auto DEFAULT_TIME = 157788000.0;         // Default endTime
    constexpr static auto DEFAULT_DELTA_T = 25000.0;          // Default delta_T
    constexpr static auto WINDOW_SIZE = 800;                  // Default window size
    constexpr static auto DEFAULT_R = 1e11;                   // Default radius R
    constexpr static auto BG_PATH = "./assets/starfield.jpg"; // Default path to the background
    constexpr static auto MAX_BODY_COUNT = 1000;              // Maximum number of CelestialBodies in the universe

    unsigned N;     // Number of bodies
    double R;       // Radius of the universe
    double curTime; // Time since the beginning of the simulation
    double endTime; // Time at which the simulation stops
    double delta_t; // Increment steps for time

    std::vector<std::unique_ptr<CelestialBody>> bodyVec; // Vector of CelestialBody objects
    sf::Texture bgTexture;                               // Background texture
    sf::Sprite bgSprite;                                 // Background sprite
};

#endif // end of Universe.hpp
