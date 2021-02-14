#ifndef _PHOTOMAGIC_H
#define _PHOTOMAGIC_H 1

#include "FibLFSR.hpp"

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


void transform(sf::Image& image, FibLFSR& L);

#endif /* End of PhotoMagic.hpp */