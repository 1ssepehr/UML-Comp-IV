// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#ifndef PS2A_SRC_UNIVERSE_HPP_
#define PS2A_SRC_UNIVERSE_HPP_

#include <istream>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "CelestialBody.hpp"

class Universe : public sf::RenderWindow {
 public:
  // Default constructor
  Universe() {}

  // Main constructor
  Universe(unsigned N, double R);

  // Extraction operator
  friend std::istream& operator>>(std::istream& in, Universe& universe);

  void load();

 private:
  void initialize();
  static const char DEFAULT_TITLE[];
  static const char BG_PATH[];  // Default path to the background
  static const double SCALE;    // Scale for the universe to display window

  double width, height;       // Dimensions of the window
  double center_x, center_y;  // Coordinates of window's center
  unsigned N;                 // Number of bodies
  double R;                   // Radius of the universe
  std::vector<std::unique_ptr<CelestialBody>> bodyVec;
  sf::Texture bgTexture;  // Background texture
  sf::Sprite bgSprite;    // Background sprite
};

#endif  // PS2A_SRC_UNIVERSE_HPP_
