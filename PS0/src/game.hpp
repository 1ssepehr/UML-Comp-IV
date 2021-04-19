// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#ifndef PS0_SRC_GAME_HPP_
#define PS0_SRC_GAME_HPP_

#include <random>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "asteroid.hpp"
#include "globals.hpp"
#include "spaceship.hpp"

class SepGame {
 public:
  SepGame();
  void load_gameOver();
  void start_game();
  void adjust_player();

 private:
  sf::RenderWindow window;
  sf::RenderWindow gameOver;
  sf::Sprite BackgroundSpr_1;
  sf::Sprite BackgroundSpr_2;
  sf::Texture BackgroundTex;

  Spaceship Player;
  std::vector<Asteroid> Obstacles;
  sf::Clock clock;

  sf::Font font;
  sf::Text label;
  bool isGameOver;

  static constexpr int ASTEROID_LIMIT = 12;
  static constexpr float PLAYER_SPEED = 7.f;
  static constexpr float BG_SPEED = 1.5f;
};

#endif  // PS0_SRC_GAME_HPP_
