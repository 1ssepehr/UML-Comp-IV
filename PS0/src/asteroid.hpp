// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#ifndef PS0_SRC_ASTEROID_HPP_
#define PS0_SRC_ASTEROID_HPP_

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "globals.hpp"

class Asteroid : public sf::Sprite {
 public:
  Asteroid();
  void fall_move();

  constexpr static float SPAWN_RATE = 5.f;

 private:
  static sf::Texture texture;
  sf::Vector2f speed;

  constexpr static float FALL_MIN_SPEED = 3.f;
  constexpr static float FALL_MAX_SPEED = 12.f;
  constexpr static float FALL_TILT_LIMIT = 1.f;
};

#endif  // PS0_SRC_ASTEROID_HPP_
