#ifndef CELESTIAL_BODY_HPP
#define CELESTIAL_BODY_HPP 1

#include <iostream>
#include <stdexcept>
#include <string>

#include <SFML/Graphics.hpp>

class Point
{
  public:
    Point(): x(0), y(0) {}
    Point(double x, double y): x(x), y(y) {}

    friend Point operator+(Point A, Point B) { return Point(A.x + B.x, A.y + B.y); }
    Point operator+=(Point other) { x += other.x; y += other.y; return *this; }
    template<typename T> friend Point operator*(T scalar, Point p) { return Point(p.x * scalar, p.y *= scalar); }

    friend std::ostream& operator<<(std::ostream& out, Point p) { return out << "(" << p.x << ", " << p.y << ")"; }

    double x, y;    
};

class CelestialBody : public sf::Drawable
{
  public:
    CelestialBody() {}
    CelestialBody(int x, int y, double v_x, double v_y, double mass, std::string name);

    void setPosition(float x, float y) { sprite.setPosition(x, y); }
    void setScale(float scale) { sprite.setScale(scale, scale); }

  private:
    // Initialize the object of the target
    void loadArtifacts();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    friend std::istream& operator>>(std::istream& in, CelestialBody& body);
    friend class Universe;

    Point r;  // Position
    Point v;  // Velocity
    Point a;  // Acceleration
    Point f;  // Net force acting on the body
    double mass = 1;

    // Runge-Kutta 4th order calculations
    Point k1r, k2r, k3r, k4r;
    Point k1v, k2v, k3v, k4v;

    std::string name;     // Path to file for the texture
    sf::Sprite sprite;
    sf::Texture texture;
};

#endif // end of CelestialBody.hpp