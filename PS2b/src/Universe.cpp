#include <SFML/Window/VideoMode.hpp>
#include <cmath>
#include <exception>
#include <iostream>
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

        step(delta_t);
        if (curTime > endTime)
            close();

        clear();
        draw(bgSprite);
        for (auto &body : bodyVec)
        {
            float x_display = getWinSpan() * (0.5 + body->x / (2 * R));
            float y_display = getWinSpan() * (0.5 + body->y / (2 * R));
            // std::cout << body.get() << std::endl;
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
    universe.create(sf::VideoMode(universe.getWinSpan(), universe.getWinSpan()),
                    universe.DEFAULT_TITLE); // Resize the window using new R and N values
    auto bgScale = universe.getWinSpan() / universe.bgSprite.getLocalBounds().width;
    universe.bgSprite.setScale(bgScale, bgScale);

    // Add N CelestialBody objects as initialized by std::istream &in
    for (auto i = 0U; i < universe.N; i++)
    {
        universe.bodyVec.push_back(std::make_unique<CelestialBody>());
        in >> *universe.bodyVec.back();
    }
    return in;
}

void Universe::step(double duration)
{
    curTime += duration;
    for (auto &body : bodyVec)
    {
        body->f_x = body->f_y = 0;
        for (auto &other : bodyVec)
        {
            if (body != other)
            {
                auto dx = other->x - body->x;
                auto dy = other->y - body->y;
                auto r = std::sqrt(dx * dx + dy * dy);
                auto f = G * body->mass * other->mass / (r * r);
                body->f_x += f * (dx / r);
                body->f_y += f * (dy / r);
            }
        }
        body->a_x = body->f_x / body->mass;
        body->a_y = body->f_y / body->mass;

        body->v_x += duration * body->a_x;
        body->v_y += duration * body->a_y;

        body->x += duration * body->v_x;
        body->y += duration * body->v_y;
    }
}

void Universe::loadArtifacts()
{
    if (!bgTexture.loadFromFile(BG_PATH))
        throw std::runtime_error("Assets are not present with the executable.");
    bgTexture.setSmooth(true);
    bgSprite.setTexture(bgTexture);
    auto scaleFactor = getWinSpan() / bgSprite.getLocalBounds().width;
    bgSprite.setScale(scaleFactor, scaleFactor);
    create(sf::VideoMode(getWinSpan(), getWinSpan()), DEFAULT_TITLE);
    setFramerateLimit(60);
}