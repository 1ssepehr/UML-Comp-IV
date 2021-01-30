#ifndef _SPACESHIP_H
#define _SPACESHIP_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "globals.hpp"

class Spaceship: public sf::Sprite
{
public:
    Spaceship();
    void move(sf::Vector2f vector);
    void fire();
private:
    static sf::Texture texture;
};

#endif