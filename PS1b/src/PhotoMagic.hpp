#ifndef _PHOTOMAGIC_H
#define _PHOTOMAGIC_H 1

#include "FibLFSR.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Encrypts an sf::Image object using a FibLFSR object.
void transform(sf::Image &image, FibLFSR &L);

#endif /* End of PhotoMagic.hpp */