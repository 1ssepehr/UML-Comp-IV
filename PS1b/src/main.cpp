// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include "FibLFSR.hpp"
#include "PhotoMagic.hpp"

// display an encrypted copy of the picture, using the LFSR to do the encryption
int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Too few arguments.\nUse:\n    $ ./PhotoMagic <input_file> "
                 "<output_file> <keyphrase>\n";
    return -1;
  }

  std::string input_path{argv[1]};
  std::string output_path{argv[2]};
  FibLFSR L(argv[3]);

  sf::Image image_in;
  std::cout << "Loading image \"" << input_path << "\"... ";
  if (!image_in.loadFromFile(input_path)) return -1;
  sf::Image image_out;
  image_out.create(image_in.getSize().x, image_in.getSize().y);
  image_out.copy(image_in, 0, 0);
  std::cout << "Done." << std::endl;

  // Encrypts image_out using our LFSR
  transform_img(&image_out, &L);

  sf::Texture texture_in, texture_out;
  texture_in.loadFromImage(image_in);
  texture_out.loadFromImage(image_out);

  sf::Sprite sprite_in, sprite_out;
  sprite_in.setTexture(texture_in);
  sprite_out.setTexture(texture_out);
  sprite_out.setPosition({sprite_in.getGlobalBounds().width, 0});

  sf::RenderWindow window(
      sf::VideoMode(2 * image_in.getSize().x, image_in.getSize().y),
      "Input vs. Output Comparison");

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    window.clear();
    window.draw(sprite_in);
    window.draw(sprite_out);
    window.display();
  }

  std::cout << "Saving image as \"" << output_path << "\"... ";
  if (!image_out.saveToFile(output_path)) return -1;
  std::cout << "Done." << std::endl;
}
