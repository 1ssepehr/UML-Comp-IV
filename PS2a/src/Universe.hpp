#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <istream>

#include "CelestialBody.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Universe: public sf::RenderWindow
{
public:
    // Default constructor
    Universe() {}

    // Main constructor
    Universe(unsigned N, double R);

    // Extraction operator
    friend std::istream& operator>>(std::istream& in, Universe& universe);

    void load();

private:
    void initialize();
    const static std::string DEFAULT_TITLE;
    const static std::string BG_PATH;  // Default path to the background
    const static double SCALE;  // Scale for the universe to display window

    double width, height;  // Dimensions of the window
    double center_x, center_y;  // Coordinates of window's center
    unsigned N;  // Number of bodies
    double R;  // Radius of the universe
    std::vector<CelestialBody> bodyVec;
    sf::Texture bgTexture;  // Background texture
    sf::Sprite bgSprite;  // Background sprite
};

#endif // end of Universe.hpp
