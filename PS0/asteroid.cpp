#include "globals.hpp"
#include "asteroid.hpp"

sf::Texture Asteroid::texture = []() {
    sf::Texture asteroidTex;
    if (!asteroidTex.loadFromFile("./assets/boulder.png"))
        throw EXIT_FAILURE;
    return asteroidTex;
}();

Asteroid::Asteroid():
    sf::Sprite(),
    speed_x(RNG * FALL_TILT_LIMIT),
    speed_y(FALL_MIN_SPEED + (RNG) * (FALL_MAX_SPEED - FALL_MIN_SPEED))
{
    setTexture(texture);
    setPosition({RNG * WIDTH, -getGlobalBounds().height});
}

void Asteroid::fall_move()
{
    move(sf::Vector2f{speed_x, speed_y});
}