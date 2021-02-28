#include <exception>
#include <memory>
#include <stdexcept>
#include <utility>

#include "CelestialBody.hpp"
#include "Universe.hpp"

void Universe::load()
{
    sf::Event event;
    while (isOpen())
    {
        while (pollEvent(event))
            if (event.type == sf::Event::Closed)
                close();

        clear();
        draw(bgSprite);
        for (auto &body : bodyVec)
        {
            float x_display = (getWinSpan() / 2) + (body->getX() / (2 * R) * getWinSpan());
            float y_display = (getWinSpan() / 2) + (body->getY() / (2 * R) * getWinSpan());
            body->setPosition(x_display, y_display);
            draw(*body);
        }
        display();
    }
}

std::istream &operator>>(std::istream &in, Universe &universe)
{
    in >> universe.N >> universe.R;
    if (universe.N > Universe::MAX_BODY_COUNT)
        throw std::runtime_error("Error: Encountered more than 1000 planets.");
    universe.setSize({static_cast<unsigned>(universe.getWinSpan()),
                      static_cast<unsigned>(universe.getWinSpan())});  // Resize the window using new R and N values

    // Add N CelestialBody objects as initialized by std::istream &in
    for (auto i = 0U; i < universe.N; i++)
    {
        auto thisBody = std::make_unique<CelestialBody>();
        std::cin >> *thisBody;
        universe.bodyVec.push_back(std::move(thisBody));
    }
    return in;
}

void Universe::step(double time)
{

}

void Universe::loadArtifacts()
{
    if (!bgTexture.loadFromFile(BG_PATH))
        throw std::runtime_error("Assets are not present with the executable.");
    bgTexture.setSmooth(true);
    bgSprite.setTexture(bgTexture);
    auto scaleFactor = getWinSpan() / bgSprite.getGlobalBounds().width;
    bgSprite.setScale(scaleFactor, scaleFactor);

    create(sf::VideoMode(getWinSpan(), getWinSpan()), DEFAULT_TITLE);
    setFramerateLimit(60);
}