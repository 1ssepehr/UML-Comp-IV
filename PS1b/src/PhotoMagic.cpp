#include "PhotoMagic.hpp"
#include "FibLFSR.hpp"

#include <cstdlib>

// display an encrypted copy of the picture, using the LFSR
// to do the encryption
int main(int argc, char *argv[])
{
    sf::Image image_in, image_out;
    if (!image_in.loadFromFile(argv[1]))
        return -1;

    if (!image_out.loadFromFile(argv[2]))
        return -1;

    std::set<unsigned> taps{};
    while (argc > 3)
        taps.insert(std::atoi(argv[--argc]));
    FibLFSR L(argv[3], taps);

    sf::Color p;
    for (int x = 0; x < image_in.getSize().x; x++)
    {
        for (int y = 0; y < image_in.getSize().y; y++)
        {
            p = image_in.getPixel(x, y);
            p.r ^= L.generate(8);
            p.g ^= L.generate(8);
            p.b ^= L.generate(8);
            image_out.setPixel(x, y, p);
        }
    }

    sf::Texture texture_in, texture_out;
    texture_in.loadFromImage(image_in);
    texture_out.loadFromImage(image_out);

    sf::Sprite sprite_in, sprite_out;
    sprite_in.setTexture(texture_in);
    sprite_out.setTexture(texture_out);

    sf::RenderWindow window_in(sf::VideoMode(image_in.getSize().x, image_in.getSize().y), "Input");
    sf::RenderWindow window_out(sf::VideoMode(image_out.getSize().x, image_out.getSize().y), "Output");

    while (window_in.isOpen() && window_out.isOpen())
    {
        sf::Event event;
        while (window_in.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_in.close();
        }
        while (window_out.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_out.close();
        }
        window_in.clear();
        window_in.draw(sprite_in);
        window_in.display();
        window_out.clear();
        window_out.draw(sprite_out);
        window_out.display();
    }

    if (!image_out.saveToFile("cat_out.png"))
        return -1;
}
