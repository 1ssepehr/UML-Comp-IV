// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <cmath>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "CircularBuffer.hpp"
#include "Guitar.hpp"
#include "StringSound.hpp"

std::vector<std::int16_t> makeSamplesFromString(StringSound *SS) {
  std::vector<std::int16_t> samples;
  SS->pluck();
  int duration = 8;  // seconds
  for (int i = 0; i < SAMPLES_PER_SEC * duration; i++) {
    SS->tic();
    samples.push_back(SS->sample());
  }
  return samples;
}

int main() {
  sf::Image image;
  if (!image.loadFromFile("./assets/keyboard.png")) return -1;
  sf::Vector2u size = image.getSize();
  sf::RenderWindow window(sf::VideoMode(size.x, size.y),
                          "SFML Plucked String Sound");
  sf::Texture texture;
  texture.loadFromImage(image);
  sf::Sprite sprite;
  sprite.setTexture(texture);
  std::vector<std::vector<std::int16_t>> samples;
  samples.reserve(keyboard_size);
  std::vector<sf::SoundBuffer> buf(keyboard_size);
  std::vector<sf::Sound> sound(keyboard_size);
  auto calculateFreq = [](auto i) {
    return CONCERT_A * pow(2, (i - 24.0) / 12.0);
  };
  for (int i = 0; i < keyboard_size; i++) {
    StringSound Guitar(calculateFreq(i));
    samples.push_back(makeSamplesFromString(&Guitar));
    if (!(buf[i]).loadFromSamples(&samples[i][0], samples[i].size(), 2,
                                  SAMPLES_PER_SEC))
      throw std::runtime_error("sf::SoundBuffer: failed to load from samples.");
    sound[i].setBuffer(buf[i]);
  }
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      if (event.type == sf::Event::TextEntered) {
        for (int i = 0; i < keyboard_size; i++) {
          if (event.text.unicode == static_cast<unsigned>(keyboard[i])) {
            std::cout << "Playing " << keyboard[i] << " note" << std::endl;
            sound[i].play();
          }
        }
      }
      window.clear();
      window.draw(sprite);
      window.display();
    }
  }
  return 0;
}
