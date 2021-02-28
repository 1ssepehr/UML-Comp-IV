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

    void setPosition(float x, float y) { sprite.setPosition(x, y); }

  private:
    // Initialize the object of the target
    void loadArtifacts();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    friend std::istream& operator>>(std::istream& in, CelestialBody& body);
    friend class Universe;

    double x = 0, y = 0;
    double v_x = 0, v_y = 0;
    double a_x = 0, a_y = 0;
    double f_x = 0, f_y = 0;
    double mass = 1;
    std::string name;
    sf::Sprite sprite;
    sf::Texture texture;
};

#endif // end of CelestialBody.hpp