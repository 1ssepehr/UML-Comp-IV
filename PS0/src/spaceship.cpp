// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include "spaceship.hpp"
#include <SFML/Graphics/Sprite.hpp>

sf::Texture Spaceship::texture = []() {
  sf::Texture eagle;
  if (!eagle.loadFromFile("./assets/eagle.png")) throw EXIT_FAILURE;
  eagle.setSmooth(true);
  return eagle;
}();

Spaceship::Spaceship() : sf::Sprite() {
  setTexture(texture);
  setPosition(WIDTH * 0.5, HEIGHT * 0.8);
}

void Spaceship::move(const sf::Vector2f &vector) {
  this->sf::Sprite::move(vector);  // NOLINT [build/include_what_you_use]
  auto curPosition = getPosition();
  auto dims = getGlobalBounds();
  if (curPosition.x > WIDTH - dims.width)  // Right constraint
    setPosition({WIDTH - dims.width, curPosition.y});
  if (curPosition.x < 0)  // Left constraint
    setPosition({0, curPosition.y});

  if (curPosition.y > HEIGHT - dims.height)  // Down constraint
    setPosition({curPosition.x, HEIGHT - dims.height});
  if (curPosition.y < HEIGHT * 0.4)  // Up constraint
    setPosition({curPosition.x, HEIGHT * 0.4});
}
