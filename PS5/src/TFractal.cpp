// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include <iostream>
#include <stdexcept>
#include <vector>

#include <SFML/Window.hpp>

#include "Triangle.hpp"

static char optionsMsg[] =
    "Invalid options. Please use:\n"
    "    `./Triangle L N',\n"
    "where:\n"
    "    L = length of base triangle's side (double), and\n"
    "    N = recursion depth (int).";

static char controlsText[] =
    "Up/Down: Increase/Decrease N\n"
    "Right/Left: Increase/Decrease L\n"
    "Enter: Change Color\n"
    "Space: Change Style\n"
    "Backspace: Show/Hide this text";

// Path to the font file for controls
static char fontPath[] = "./assets/Oxanium.ttf";

// Series of dark colors to be used for the triangles
sf::Color colors[] = {
    sf::Color(128, 0, 0),    sf::Color(220, 20, 60),  sf::Color(205, 92, 92),
    sf::Color(184, 134, 11), sf::Color(128, 128, 0),  sf::Color(85, 107, 47),
    sf::Color(0, 100, 0),    sf::Color(46, 139, 87),  sf::Color(47, 79, 79),
    sf::Color(70, 130, 180), sf::Color(25, 25, 112),  sf::Color(139, 0, 139),
    sf::Color(128, 0, 128),  sf::Color(199, 21, 133), sf::Color(139, 69, 19),
    sf::Color(112, 128, 144)};
auto colorCount = sizeof(colors) / sizeof(colors[0]);

// Recursive function to initalize the vector of triangles
void fTree(std::vector<Triangle> *shapes, Point center, double L, int n,
           sf::PrimitiveType type, int colorKey) {
  if (n < 0) return;
  if (L < 0) L = 0;

  shapes->push_back(Triangle(center, L, colors[colorKey % colorCount], type));

  auto A = L * std::cos(M_PI / 6.0);  // Altitude of the triangle

  Point right = {center.x + (L * 0.75), center.y - (A / 6.0)};
  Point left = {center.x - (L * 0.5), center.y - (A * 2.0 / 3.0)};
  Point bottom = {center.x - (L * 0.25), center.y + (A * 5.0 / 6.0)};

  fTree(shapes, right, 0.5 * L, n - 1, type, colorKey + 1);
  fTree(shapes, left, 0.5 * L, n - 1, type, colorKey + 1);
  fTree(shapes, bottom, 0.5 * L, n - 1, type, colorKey + 1);
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << optionsMsg << std::endl;
    return -1;
  }

  try {
    // Load Sierpinsky triangle arguments
    auto L = std::stod(argv[1]);  // Length of triangle
    auto N = std::stoi(argv[2]);  // Recursion depth level
    auto drawType = sf::Triangles;  // Type of drawing (hollow or filled)
    auto colorKey = 0;  // Base color for the first triangle
    std::vector<Triangle> triangles{};

    // Create RenderWindow
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    auto w_size = 960;
    sf::RenderWindow window(sf::VideoMode(w_size, w_size),
                            "Sierpinski's Triangle", sf::Style::Default,
                            settings);
    window.setPosition({150, 50});
    window.setFramerateLimit(60);

    // Controls text on the screen
    sf::Font font;
    if (!font.loadFromFile(fontPath))
      throw std::runtime_error("Assets not present with the program!");
    sf::Text controls(controlsText, font, 20);
    controls.setFillColor(sf::Color::Black);
    bool showControls = true;

    // Program event loop
    while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) switch (event.type) {
          case sf::Event::Closed:
            window.close();
            break;
          case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) L -= 20;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) L += 20;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) --N;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ++N;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) ++colorKey;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
              drawType =
                  (drawType == sf::Triangles) ? sf::LineStrip : sf::Triangles;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
              showControls ^= 1;
            if (N < 0) N = 0;
            if (L < 0) L = 0;
            break;
          default:
            break;
        }

      // Recalculate the triangles with [potentially new] parameters
      triangles.clear();
      fTree(&triangles, {0.5 * w_size, 0.5 * w_size}, L, N, drawType, colorKey);

      // Draw triangles onto the canvas
      window.clear(sf::Color::White);
      for (auto& x : triangles) window.draw(x);
      if (showControls) window.draw(controls);
      window.display();
    }
  } catch (std::invalid_argument &e) {
    std::cerr << optionsMsg << std::endl;
    return -1;
  } catch (std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}
