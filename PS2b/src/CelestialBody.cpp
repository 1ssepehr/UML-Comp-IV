// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include "CelestialBody.hpp"

#include <iomanip>

CelestialBody::CelestialBody(int x, int y, double v_x, double v_y, double mass,
                             std::string filename)
    : r(x, y), v(v_x, v_y), mass(mass), filename(filename) {
  loadArtifacts();
}

std::istream &operator>>(std::istream &in, CelestialBody &body) {
  in >> body.r.x >> body.r.y >> body.v.x >> body.v.y >> body.mass >>
      body.filename;
  body.loadArtifacts();
  return in;
}

std::ostream &operator<<(std::ostream &out, CelestialBody &body) {
  out << std::setw(14) << body.r.x << std::setw(14) << body.r.y;
  out << std::setw(14) << body.v.x << std::setw(14) << body.v.y;
  out << std::setw(14) << body.mass << std::setw(14) << body.filename;
  return out;
}

void CelestialBody::loadArtifacts() {
  std::string path = "./assets/" + filename;
  if (!texture.loadFromFile(path))
    throw std::invalid_argument("Texture filename not found.");
  sprite.setTexture(texture);
}

void CelestialBody::draw(sf::RenderTarget &target,
                         sf::RenderStates states) const {
  target.draw(sprite, states);
}
