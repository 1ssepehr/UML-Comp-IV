#ifndef _ASTEROIDS_H
#define _ASTEROIDS_H

#include "globals.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Asteroid: public sf::Sprite
{
public:
    Asteroid();
    void fall_move();

    constexpr static float SPAWN_RATE = 5.f;
private:
    static sf::Texture texture;
    float speed_x;
    float speed_y;

    constexpr static float FALL_MIN_SPEED = 3.f;
    constexpr static float FALL_MAX_SPEED = 12.f;
    constexpr static float FALL_TILT_LIMIT = 1.f;
};

#endif