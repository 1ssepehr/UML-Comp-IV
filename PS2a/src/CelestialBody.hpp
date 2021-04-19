// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#ifndef PS2A_SRC_CELESTIALBODY_HPP_
#define PS2A_SRC_CELESTIALBODY_HPP_ 1

#include <iostream>
#include <stdexcept>
#include <string>

#include <SFML/Graphics.hpp>

class CelestialBody : public sf::Drawable {
 public:
  CelestialBody() {}
  CelestialBody(int x, int y, double v_x, double v_y, double mass,
                std::string name);

  double getX() const { return x; }
  double getY() const { return y; }

  void setPosition(float x, float y) { sprite.setPosition(x, y); }

 private:
  void initialize();
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;  // NOLINT

  friend std::istream& operator>>(std::istream& in, CelestialBody& body);

  double x;
  double y;
  double v_x;
  double v_y;
  double mass;
  std::string name;
  sf::Sprite sprite;
  sf::Texture texture;
};

#endif  // PS2A_SRC_CELESTIALBODY_HPP_
