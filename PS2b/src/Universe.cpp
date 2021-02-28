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
            float x_display = getWinSpan() * (0.5 + body->r.x / (2 * R));
            float y_display = getWinSpan() * (0.5 + body->r.y / (2 * R));
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
        body->f.x = body->f.y = 0;
        for (auto &other : bodyVec)
        {
            if (body != other)
            {
                auto dx = other->r.x - body->r.x;
                auto dy = other->r.y - body->r.y;
                auto r = std::sqrt(dx * dx + dy * dy);
                auto f = G * body->mass * other->mass / (r * r);
                body->f.x += f * (dx / r);
                body->f.y += f * (dy / r);
            }
        }
        body->a.x = body->f.x / body->mass;
        body->a.y = body->f.y / body->mass;

        body->v.x += duration * body->a.x;
        body->v.y += duration * body->a.y;

        body->r.x += duration * body->v.x;
        body->r.y += duration * body->v.y;
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