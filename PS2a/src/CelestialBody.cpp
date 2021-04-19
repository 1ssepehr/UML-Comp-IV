// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include "CelestialBody.hpp"

CelestialBody::CelestialBody(int x, int y, double v_x, double v_y, double mass,
                             std::string name)
    : x(x), y(y), v_x(v_x), v_y(v_y), mass(mass) {
  initialize();
}

std::istream& operator>>(std::istream& in, CelestialBody& body) {
  in >> body.x >> body.y >> body.v_x >> body.v_y >> body.mass >> body.name;
  body.initialize();
  return in;
}

void CelestialBody::initialize() {
  std::string path = "./assets/" + name;
  if (!texture.loadFromFile(path))
    throw std::invalid_argument("Texture filename not found.");
  sprite.setTexture(texture);
}

void CelestialBody::draw(sf::RenderTarget& target,
                         sf::RenderStates states) const {
  target.draw(sprite, states);
}
