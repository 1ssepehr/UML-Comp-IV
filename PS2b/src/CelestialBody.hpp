#ifndef CELESTIAL_BODY_HPP
#define CELESTIAL_BODY_HPP 1

#include <iostream>
#include <stdexcept>
#include <string>

#include <SFML/Graphics.hpp>

class CelestialBody : public sf::Drawable
{
  public:
    CelestialBody() {}
    CelestialBody(int x, int y, double v_x, double v_y, double mass, std::string name);

    double getX() const { return x; }
    double getY() const { return y; }

    void setPosition(float x, float y) { sprite.setPosition(x, y); }
  
  private:
    // Initialize the object of the target
    void initialize();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    friend std::istream& operator>>(std::istream& in, CelestialBody& body);

    double x, y;
    double v_x, v_y;
    double f_x, f_y;
    double mass;
    std::string name;
    sf::Sprite sprite;
    sf::Texture texture;
};

#endif // end of CelestialBody.hpp