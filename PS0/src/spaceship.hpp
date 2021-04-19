// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#ifndef PS0_SRC_SPACESHIP_HPP_
#define PS0_SRC_SPACESHIP_HPP_

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "globals.hpp"

class Spaceship : public sf::Sprite {
 public:
  Spaceship();
  void move(const sf::Vector2f &vector);  // NOLINT [build/include_what_you_use]

 private:
  static sf::Texture texture;
};

#endif  // PS0_SRC_SPACESHIP_HPP_
