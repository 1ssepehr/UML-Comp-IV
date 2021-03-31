// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#ifndef PS5_SRC_TRIANGLE_HPP_
#define PS5_SRC_TRIANGLE_HPP_

#include <cmath>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

typedef sf::Vector2<double> Point;

class Triangle : public sf::Drawable {
 public:
  Triangle(Point center, double length, sf::Color color = sf::Color::White)
      : vertices(sf::Triangles, 3) {
    auto height = length * std::cos(30);
    auto radius = height * 2.0 / 3.0;
    vertices[0].position =
        sf::Vector2f(center.x, center.y - radius);  // top vertex
    vertices[1].position = sf::Vector2f(
        center.x + (0.5 * length), center.y + (0.5 * radius));  // right vertex
    vertices[2].position = sf::Vector2f(
        center.x - (0.5 * length), center.y + (0.5 * radius));  // left vertex

    vertices[0].color = vertices[1].color = vertices[2].color = color;
  }

 private:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(vertices, states);
  }

  sf::VertexArray vertices;
};

#endif  // PS5_SRC_TRIANGLE_HPP_
