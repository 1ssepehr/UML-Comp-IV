#include "spaceship.hpp"

sf::Texture Spaceship::texture = []() {
    sf::Texture eagle;
    if (!eagle.loadFromFile("./assets/eagle.png"))
        throw EXIT_FAILURE;
    eagle.setSmooth(true);
    return eagle;
}();

Spaceship::Spaceship(): sf::Sprite()
{
    setTexture(texture);
    setPosition(WIDTH * 0.5, HEIGHT * 0.8);
}

void Spaceship::move(sf::Vector2f vector)
{
    sf::Sprite::move(vector);
    auto curPosition = getPosition();
    auto dims = getGlobalBounds();
    if (curPosition.x > WIDTH - dims.width) // Right constraint
        setPosition({WIDTH - dims.width, curPosition.y});
    if (curPosition.x < 0) // Left constraint
        setPosition({0, curPosition.y});

    if (curPosition.y > HEIGHT - dims.height) // Down constraint
        setPosition({curPosition.x, HEIGHT - dims.height});
    if (curPosition.y < HEIGHT * 0.4) // Up constraint
        setPosition({curPosition.x, HEIGHT * 0.4});
}

void Spaceship::fire()
{
    
}
