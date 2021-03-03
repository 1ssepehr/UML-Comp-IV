#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include "CelestialBody.hpp"
#include "Universe.hpp"

void Universe::load()
{
    bgMusic.play();
    sf::Event event;
    while (isOpen())
    {
        while (pollEvent(event))
            if (event.type == sf::Event::Closed)
                close();

        step(delta_t);
        if (curTime > endTime)
            close();

        // Printing time
        auto days = curTime / SECS_IN_DAY;
        std::stringstream timer_text;
        timer_text << "Timer: " << std::fixed << std::setprecision(2) << days << " days ";
        timer_text << "(" << std::fixed << std::setprecision(1) << 100 * (curTime / endTime) << "%)" << std::endl;
        timer_text << "[=" << std::fixed << std::setprecision(0) << curTime << " seconds]";
        timer.setString(timer_text.str());

        clear();
        draw(bgSprite);
        draw(timer);
        for (auto &body : bodyVec)
        {
            float x_display = getSize().x * (0.5 + body->r.x / (2 * R));
            // Doing (-body->r.y) since y-axis is inverted in SFML
            float y_display = getSize().x * (0.5 - body->r.y / (2 * R));
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
    auto bgScale = universe.getSize().x / universe.bgSprite.getLocalBounds().width;
    universe.bgSprite.setScale(bgScale, bgScale);

    // Add N CelestialBody objects as initialized by std::istream &in
    for (auto i = 0U; i < universe.N; i++)
    {
        universe.bodyVec.push_back(std::make_unique<CelestialBody>());
        in >> *universe.bodyVec.back();
        universe.bodyVec.back()->setScale(bgScale);
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, Universe &universe)
{
    out << universe.N << std::endl;
    out << universe.R << std::endl;
    for (auto &body : universe.bodyVec)
        out << *body << std::endl;
    return out;
}

// This step function uses the Runge-Kutta method of 4th order for estimating the position
// of the planets after a change of `h` in time. This is more calculation-heavy, but results
// in much much approximation error, and the trade-off makes the simulation more accurate overall.
void Universe::step(double h)
{
    curTime += h;

    std::vector<Point> net_force(N);
    std::vector<double> mass(N);
    for (unsigned i = 0; i < N; i++)
        mass[i] = bodyVec[i]->mass;
    std::vector<Point> position(N);

    // Function to calculate forces based on given position (position) and mass (mass).
    // Updates the content of `std::vector<Point> net_force` with the new calculated forces.
    // We use this function multiple times for approximations of Runge-Kutta method.
    auto calculate_forces = [](const std::vector<Point> &position, const std::vector<double> &mass,
                               std::vector<Point> &net_force) {
        unsigned N = position.size();
        for (unsigned i = 0; i < N; i++)
        {
            net_force[i] = {0, 0};
            for (unsigned j = 0; j < N; j++)
            {
                if (i == j)
                    continue;
                Point displacement{position[j].x - position[i].x, position[j].y - position[i].y};
                auto displacement_squared = (displacement.x * displacement.x) + (displacement.y * displacement.y);
                auto f_g = Universe::G * mass[j] * std::pow(displacement_squared, -1.5);

                net_force[i].x += f_g * displacement.x;
                net_force[i].y += f_g * displacement.y;
            }
        }
    };

    // Step 1 of Runge-Kutta method
    for (unsigned i = 0; i < N; i++)
        position[i] = bodyVec[i]->r;
    calculate_forces(position, mass, net_force);

    for (unsigned i = 0; i < N; i++)
    {
        bodyVec[i]->k1r = bodyVec[i]->v;
        bodyVec[i]->k1v = net_force[i];
    }

    // Step 2 of Runge-Kutta method
    for (unsigned i = 0; i < N; i++)
        position[i] = bodyVec[i]->r + (h / 2) * bodyVec[i]->k1r;
    calculate_forces(position, mass, net_force);

    for (unsigned i = 0; i < N; i++)
    {
        bodyVec[i]->k2r = bodyVec[i]->v + (h / 2) * bodyVec[i]->k1v;
        bodyVec[i]->k2v = net_force[i];
    }

    // Step 3 of Runge-Kutta method
    for (unsigned i = 0; i < N; i++)
        position[i] = bodyVec[i]->r + (h / 2) * bodyVec[i]->k2r;
    calculate_forces(position, mass, net_force);

    for (unsigned i = 0; i < N; i++)
    {
        bodyVec[i]->k3r = bodyVec[i]->v + (h / 2) * bodyVec[i]->k2v;
        bodyVec[i]->k3v = net_force[i];
    }

    // Step 4 of Runge-Kutta method
    for (unsigned i = 0; i < N; i++)
        position[i] = bodyVec[i]->r + h * bodyVec[i]->k3r;
    calculate_forces(position, mass, net_force);

    for (unsigned i = 0; i < N; i++)
    {
        bodyVec[i]->k4r = bodyVec[i]->v + h * bodyVec[i]->k3v;
        bodyVec[i]->k4v = net_force[i];
    }

    // Update the values of next step for each body
    for (auto &M : bodyVec)
    {
        M->v += (h / 6) * (M->k1v + 2.0 * M->k2v + 2.0 * M->k3v + M->k4v);
        M->r += (h / 6) * (M->k1r + 2.0 * M->k2r + 2.0 * M->k3r + M->k4r);
    }
}

void Universe::loadArtifacts()
{
    if (!timer_font.loadFromFile(FONT_PATH) || !bgMusic.openFromFile(MUSIC_PATH) || !bgTexture.loadFromFile(BG_PATH))
        throw std::runtime_error("Assets are not present with the executable.");
    bgMusic.setLoop(true);
    timer.setString("");
    timer.setFont(timer_font);
    timer.setCharacterSize(32);
    timer.setPosition(20, 20);
    bgTexture.setSmooth(true);
    bgSprite.setTexture(bgTexture);
    auto scaleFactor = getSize().x / bgSprite.getLocalBounds().width;
    bgSprite.setScale(scaleFactor, scaleFactor);
    create(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), DEFAULT_TITLE);
    setFramerateLimit(144);
}