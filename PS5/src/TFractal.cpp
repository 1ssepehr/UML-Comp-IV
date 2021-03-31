// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include <iostream>
#include <stdexcept>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window.hpp>

#include "Triangle.hpp"

static char optionsMsg[] =
    "Invalid options. Please use:\n    `./Triangle L N',\nwhere:\n    L = "
    "length of the side of the base equilateral triangle (double), and\n    "
    "N = the depth of the recursion (int).";

std::vector<Triangle> items {};

void fTree(Point center, double length, int n) {
  if (n < 0) return;
  Triangle triangle(center, length);
  items.push_back(triangle);
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << optionsMsg << std::endl;
    return -1;
  }

  try {
    auto L = std::stod(argv[1]);
    auto N = std::stoi(argv[2]);
    std::cout << "L = " << L << std::endl;
    std::cout << "N = " << N << std::endl;
  } catch (std::invalid_argument& e) {
    std::cerr << optionsMsg << std::endl;
    return -1;
  }

  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(sf::VideoMode(400, 400), "Sierpinski's Triangle",
                          sf::Style::Default, settings);
  window.setFramerateLimit(60);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event))
      if (event.type == sf::Event::Closed) window.close();
    window.clear(sf::Color::Black);
    for (auto &x : items)
      window.draw(x);
    window.display();
  }

  return 0;
}
