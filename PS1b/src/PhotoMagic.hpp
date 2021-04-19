// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#ifndef PS1B_SRC_PHOTOMAGIC_HPP_
#define PS1B_SRC_PHOTOMAGIC_HPP_ 1

#include "FibLFSR.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Encrypts an sf::Image object using a FibLFSR object.
void transform_img(sf::Image *image, FibLFSR *L);

#endif  // PS1B_SRC_PHOTOMAGIC_HPP_
