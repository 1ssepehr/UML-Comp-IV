// (C) Copyright Seyedsepehr Madani, 2021.
// Distributed under MIT license, available at
// https://opensource.org/licenses/MIT.

#include "game.hpp"

#include <cmath>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>

#include "asteroid.hpp"
#include "spaceship.hpp"

SepGame::SepGame() {
  // Create the main window
  window.create(sf::VideoMode(WIDTH, HEIGHT), "Assignment PS0 - Madani");
  window.setFramerateLimit(60);

  // Load textures
  if (!BackgroundTex.loadFromFile("./assets/space.jpeg")) throw EXIT_FAILURE;
  BackgroundTex.setSmooth(true);
  BackgroundTex.setRepeated(true);

  // Load background sprite
  BackgroundSpr_1.setTexture(BackgroundTex);
  BackgroundSpr_2.setTexture(BackgroundTex);

  BackgroundSpr_1.setPosition({0.f, -BackgroundSpr_1.getGlobalBounds().height});
  BackgroundSpr_2.setPosition({0.f, 0.f});

  // Set up the environment
  std::srand(std::time(nullptr));
  isGameOver = false;
}

void SepGame::load_gameOver() {
  sf::Font font;
  if (!font.loadFromFile("./assets/Ubuntu-R.ttf")) throw EXIT_FAILURE;
  label.setFont(font);
  label.setString("You lost! Game over...\nPress [Enter] to exit...");
  label.setCharacterSize(32);
  label.setFillColor(sf::Color::Red);
  label.setPosition({25, 25});
  gameOver.create(sf::VideoMode(400, 200), "Game Over!");
  gameOver.clear(sf::Color::White);
  gameOver.draw(label);
  gameOver.display();
  while (gameOver.isOpen()) {
    sf::Event enterKeyEvent;
    while (gameOver.pollEvent(enterKeyEvent))
      if (enterKeyEvent.type == sf::Event::KeyPressed &&
          sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        gameOver.close();
        window.close();
        return;
      }
  }
}

void SepGame::start_game() {
  sf::Vector2f movement;
  clock.restart();
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        default:
          break;
      }
    }
    // Move background
    BackgroundSpr_1.move({0.f, BG_SPEED});
    BackgroundSpr_2.move({0.f, BG_SPEED});
    auto bg_height = BackgroundSpr_1.getGlobalBounds().height;
    if (BackgroundSpr_1.getPosition().y > bg_height)
      BackgroundSpr_1.setPosition({0.f, -bg_height});
    if (BackgroundSpr_2.getPosition().y > bg_height)
      BackgroundSpr_2.setPosition({0.f, -bg_height});

    // Move Player
    movement.x = movement.y = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      movement.x = -PLAYER_SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      movement.x = PLAYER_SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      movement.y = -PLAYER_SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      movement.y = PLAYER_SPEED;
    Player.move(movement);

    // Randomly add asteroids
    if (clock.getElapsedTime().asSeconds() >= (1.0 / Asteroid::SPAWN_RATE)) {
      clock.restart();
      if (Obstacles.size() <= ASTEROID_LIMIT) Obstacles.push_back(Asteroid());
    }

    // Moving asteroids
    auto it = Obstacles.begin();
    while (it != Obstacles.end()) {
      it->fall_move();
      if (it->getPosition().y > HEIGHT)  // Remove out-of-window asteroids
        Obstacles.erase(it++);
      else
        ++it;
    }

    // Collision calculation
    for (auto asteroid : Obstacles) {
      auto PlayerPos = Player.getPosition();
      auto AsteroidPos = asteroid.getPosition();
      auto PlayerDims = Player.getGlobalBounds();
      auto BoudlderDims = asteroid.getGlobalBounds();
      if (std::fabs(PlayerPos.x - AsteroidPos.x) <
              0.8 * (PlayerDims.width + BoudlderDims.width) / 2 &&
          std::fabs(PlayerPos.y - AsteroidPos.y) <
              0.8 * (PlayerDims.height + BoudlderDims.height) / 2) {
        isGameOver = true;
      }
    }

    // Clear / Draw / Display cycle
    if (!isGameOver) {
      window.clear(sf::Color::Black);
      window.draw(BackgroundSpr_1);
      window.draw(BackgroundSpr_2);
      window.draw(Player);
      for (auto boulder : Obstacles) window.draw(boulder);
      window.display();
    } else {
      Player.setColor(sf::Color(255, 0, 0));
      load_gameOver();
    }
  }
}

void SepGame::adjust_player() {
  auto curPosition = Player.getPosition();
  auto dims = Player.getGlobalBounds();
  if (curPosition.x > WIDTH - dims.width)  // Right constraint
    Player.setPosition({WIDTH - dims.width, curPosition.y});
  if (curPosition.x < 0)  // Left constraint
    Player.setPosition({0, curPosition.y});

  if (curPosition.y > HEIGHT - dims.height)  // Down constraint
    Player.setPosition({curPosition.x, HEIGHT - dims.height});
  if (curPosition.y < HEIGHT * 0.4)  // Up constraint
    Player.setPosition({curPosition.x, HEIGHT * 0.4});
}

int main() {
  try {
    SepGame gameInstance;
    gameInstance.start_game();
  } catch (int e) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
