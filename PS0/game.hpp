#ifndef _GAME_H
#define _GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include "globals.hpp"
#include "spaceship.hpp"
#include "asteroid.hpp"

#include <string>
#include <vector>
#include <random>


class SepGame
{
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

    constexpr static int ASTEROID_LIMIT = 12;
    constexpr static float PLAYER_SPEED = 7.f;
    constexpr static float BG_SPEED = 1.5f;
};

#endif
