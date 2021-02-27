#include <exception>
#include <memory>
#include <stdexcept>
#include <utility>

#include "CelestialBody.hpp"
#include "Universe.hpp"

const std::string Universe::DEFAULT_TITLE = "Universe";
const std::string Universe::BG_PATH = "./assets/starfield.jpg";
const double Universe::SCALE = 1.6e-9;

Universe::Universe(unsigned N, double R) : N(N), R(R)
{
    initialize();
}

void Universe::load()
{
    for (unsigned i = 0; i < N; i++)
    {
        auto thisBody = std::make_unique<CelestialBody>();
        std::cin >> *thisBody;
        bodyVec.push_back(std::move(thisBody));
    }

    sf::Event event;
    while (isOpen())
    {
        while (pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                close();
                break;

            default:
                break;
            }
        }

        clear();
        draw(bgSprite);
        for (auto &body : bodyVec)
        {
            float x_display = center_x + (body->getX() / (2 * R) * width);
            float y_display = center_y + (body->getY() / (2 * R) * height);
            body->setPosition(x_display, y_display);
            draw(*body);
        }
        display();
    }
}

std::istream &operator>>(std::istream &in, Universe &universe)
{
    in >> universe.N >> universe.R;
    universe.initialize();
    return in;
}

void Universe::initialize()
{
    width = 2 * R * SCALE;
    height = 2 * R * SCALE;
    center_x = width / 2.0;
    center_y = height / 2.0;

    if (!bgTexture.loadFromFile(BG_PATH))
        throw std::runtime_error("Assets are not present with the executable.");
    bgTexture.setSmooth(true);
    bgSprite.setTexture(bgTexture);
    auto scaleFactor = width / bgSprite.getGlobalBounds().width;
    bgSprite.setScale(scaleFactor, scaleFactor);

    create(sf::VideoMode(width, height), DEFAULT_TITLE);
    setFramerateLimit(60);
}