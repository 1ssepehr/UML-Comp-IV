// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#ifndef PS5_SRC_TRIANGLE_HPP_
#define PS5_SRC_TRIANGLE_HPP_

#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

typedef sf::Vector2<double> Point;

class Triangle : public sf::Drawable {
 public:
  Triangle(Point center, double length, sf::Color color = sf::Color::Black,
           sf::PrimitiveType type = sf::LineStrip);

 private:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const {  // NOLINT
    target.draw(vertices, states);
  }

  sf::VertexArray vertices;
};

#endif  // PS5_SRC_TRIANGLE_HPP_
