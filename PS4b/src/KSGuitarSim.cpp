#include <limits.h>
#include <math.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "CircularBuffer.hpp"
#include "StringSound.hpp"

constexpr static auto CONCERT_A = 220.0;
constexpr static auto SAMPLES_PER_SEC = 44100;
constexpr static auto keyboard_size = 37;

std::vector<sf::Int16> makeSamplesFromString(StringSound *gs) {
  std::vector<sf::Int16> samples;
  gs->pluck();
  int duration = 8;  // seconds
  for (int i = 0; i < SAMPLES_PER_SEC * duration; i++) {
    gs->tic();
    samples.push_back(gs->sample());
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
  sf::Event event;
  std::vector<std::vector<sf::Int16>> samples;
  samples.reserve(keyboard_size);
  std::vector<sf::SoundBuffer> buf(keyboard_size);
  std::vector<sf::Sound> sound(keyboard_size);
  char keyboard[] = "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/’ ";
  for (int i = 0; i < keyboard_size; i++) {
    StringSound gs(CONCERT_A * pow(2, (i - 24.0) / 12.0));
    samples.push_back(makeSamplesFromString(&gs));
    if (!(buf[i]).loadFromSamples(&samples[i][0], samples[i].size(), 2,
                                  SAMPLES_PER_SEC))
      throw std::runtime_error("sf::SoundBuffer: failed to load from samples.");
    sound[i].setBuffer(buf[i]);
  }
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      for (int i = 0; i < keyboard_size; i++) {
        if (event.type == sf::Event::TextEntered) {
          if (event.text.unicode == (unsigned)keyboard[i]) {
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