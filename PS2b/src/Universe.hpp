// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#ifndef PS2B_SRC_UNIVERSE_HPP_
#define PS2B_SRC_UNIVERSE_HPP_ 1

#include <istream>
#include <memory>
#include <stdexcept>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "CelestialBody.hpp"

class Universe : public sf::RenderWindow {
 public:
  // Default constructor
  Universe()
      : N(0),
        R(DEFAULT_R),
        curTime(0),
        endTime(DEFAULT_TIME),
        delta_t(DEFAULT_DELTA_T) {
    loadArtifacts();
  }

  // Main constructor
  Universe(double endTime, double delta_t)
      : N(0), R(DEFAULT_R), curTime(0), endTime(endTime), delta_t(delta_t) {
    if (endTime <= 0)
      throw std::invalid_argument(
          "Error: Given T (end time for Universe object) is negative.");
    loadArtifacts();
  }

  // Extraction operator for reading N, R from input stream
  friend std::istream &operator>>(std::istream &in, Universe &universe);

  // Insertion operator for outputing the state of the universe
  friend std::ostream &operator<<(std::ostream &out, Universe &universe);

  // Loads the window of simulation
  void load();

  constexpr static auto G = 6.674e-11;  // Gravitational Constant

 private:
  // Reads assets and initializes SFML artifacts for simulation based on N, R
  // value
  void loadArtifacts();

  // Steps once through time (by delta_t) and moves the
  void step(double time);

  static constexpr auto DEFAULT_TITLE = "Universe";  // Default window title
  static constexpr auto DEFAULT_TIME = 157788000.0;  // Default endTime
  static constexpr auto DEFAULT_DELTA_T = 25000.0;   // Default delta_T
  static constexpr auto WINDOW_SIZE = 800;           // Default window size
  static constexpr auto DEFAULT_R = 1e11;            // Default radius R
  static constexpr auto BG_PATH =
      "./assets/space.png";  // Default path to the background
  constexpr static auto MUSIC_PATH =
      "./assets/LunarLiftoff.wav";  // Default path to music
  constexpr static auto FONT_PATH =
      "./assets/Oxanium.ttf";  // Default path to font
  constexpr static auto MAX_BODY_COUNT =
      1000;  // Maximum number of CelestialBodies in the universe
  constexpr static auto SECS_IN_DAY = 86400;  // Number of seconds in a day

  unsigned N;      // Number of bodies
  double R;        // Radius of the universe
  double curTime;  // Time since the beginning of the simulation
  double endTime;  // Time at which the simulation stops
  double delta_t;  // Increment steps for time

  std::vector<std::unique_ptr<CelestialBody>>
      bodyVec;            // Vector of CelestialBody objects
  sf::Music bgMusic;      // Background music
  sf::Font timer_font;    // Font for timer
  sf::Text timer;         // Timer for displaying elapsed time
  sf::Texture bgTexture;  // Background texture
  sf::Sprite bgSprite;    // Background sprite
};

#endif  // PS2B_SRC_UNIVERSE_HPP_
