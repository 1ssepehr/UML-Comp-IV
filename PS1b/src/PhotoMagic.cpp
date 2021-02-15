#include "PhotoMagic.hpp"

#include <cstddef>
#include <iostream>

void transform(sf::Image &image, FibLFSR &L)
{
    int percent;
    int progress = 0;
    std::cout << "Processing image..." << std::endl;

    sf::Color p;
    auto size = image.getSize();
    for (size_t x = 0; x < size.x; x++)
    {
        for (size_t y = 0; y < size.y; y++)
        {
            p = image.getPixel(x, y);
            p.r ^= L.generate(8);
            p.g ^= L.generate(8);
            p.b ^= L.generate(8);
            image.setPixel(x, y, p);
            
            percent = 60 * ((y + 1) + ((x + 1) * size.y))/(size.x * size.y);
            if (percent >= progress)
            {
                std::cout << "\r" << "[" << std::string(percent, '=') << std::string(60 - percent, ' ') << "] ";
                std::cout << (percent * 100) / 60 << "%";
                std::cout.flush();
                progress++;
            }
        }
    }
    std::cout << "\nProcess Complete." << std::endl;
}

