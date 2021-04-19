// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include "asteroid.hpp"

#include "globals.hpp"

sf::Texture Asteroid::texture = []() {
  sf::Texture asteroidTex;
  if (!asteroidTex.loadFromFile("./assets/boulder.png")) throw EXIT_FAILURE;
  return asteroidTex;
}();

Asteroid::Asteroid()
    : sf::Sprite(),
      speed(RNG * FALL_TILT_LIMIT,
            FALL_MIN_SPEED + (RNG) * (FALL_MAX_SPEED - FALL_MIN_SPEED)) {
  setTexture(texture);
  setPosition({RNG * WIDTH, -getGlobalBounds().height});
}

void Asteroid::fall_move() { this->move(speed); }
