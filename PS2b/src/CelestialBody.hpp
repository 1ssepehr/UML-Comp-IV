#ifndef CELESTIAL_BODY_HPP
#define CELESTIAL_BODY_HPP 1

#include <iostream>
#include <stdexcept>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

typedef sf::Vector2<double> Point;
class CelestialBody : public sf::Drawable
{
  public:
    CelestialBody()
    {
    }
    CelestialBody(int x, int y, double v_x, double v_y, double mass, std::string filename);

    void setPosition(float x, float y)
    {
        sprite.setPosition(x, y);
    }
    void setScale(float scale)
    {
        sprite.setScale(scale, scale);
    }

  private:
    // Initialize the object of the target
    void loadArtifacts();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    friend std::istream &operator>>(std::istream &in, CelestialBody &body);
    friend std::ostream &operator<<(std::ostream &out, CelestialBody &body);
    friend class Universe;

    Point r; // Position
    Point v; // Velocity
    Point a; // Acceleration
    Point f; // Net force acting on the body
    double mass = 1;

    // Runge-Kutta 4th order calculations
    Point k1r, k2r, k3r, k4r;
    Point k1v, k2v, k3v, k4v;

    std::string filename; // Path to file for the texture
    sf::Sprite sprite;
    sf::Texture texture;
};

#endif // end of CelestialBody.hpp