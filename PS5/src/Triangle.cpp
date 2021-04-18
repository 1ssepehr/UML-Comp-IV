// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include "Triangle.hpp"

Triangle::Triangle(Point center, double L, sf::Color color,
                   sf::PrimitiveType type)
    : vertices(type, 4) {
  auto altitude = L * std::cos(M_PI / 6.0);
  auto radius = altitude * 2.0 / 3.0;
  vertices[0].position =
      sf::Vector2f(center.x, center.y + radius);  // bottom vertex
  vertices[1].position = sf::Vector2f(
      center.x + (0.5 * L), center.y - (0.5 * radius));  // right vertex
  vertices[2].position = sf::Vector2f(
      center.x - (0.5 * L), center.y - (0.5 * radius));  // left vertex
  vertices[3].position = vertices[0].position;

  vertices[0].color = vertices[1].color = vertices[2].color =
      vertices[3].color = color;
}
