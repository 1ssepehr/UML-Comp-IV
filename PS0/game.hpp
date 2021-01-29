#ifndef _GAME_H
#define _GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>

#include <string>
#include <list>
#include <random>

#define RNG ((float) std::rand() / (float) RAND_MAX) // float random in [0, 1)

class Boulder: public sf::Sprite
{
public:
    Boulder();
    void move();

    constexpr static float SPAWN_RATE = 5.f;
private:
    sf::Texture texture;
    float speed_x;
    float speed_y;
    float speed_r;

    constexpr static float FALL_MIN_SPEED = 3.f;
    constexpr static float FALL_MAX_SPEED = 12.f;
    constexpr static float FALL_TILT_LIMIT = 1.f;

};

class SepGame
{
public:
    SepGame();
    void load_gameOver();
    void start_game();
    void adjust_player();

    constexpr static int WIDTH = 960;
    constexpr static int HEIGHT = 800;
private:
    sf::RenderWindow window;
    sf::RenderWindow gameOver;
    sf::Sprite PlayerSpr;
    sf::Sprite BackgroundSpr_1;
    sf::Sprite BackgroundSpr_2;
    sf::Texture PlayerTex;
    sf::Texture BackgroundTex;
    sf::Texture BoulderTex;
    std::list<Boulder> Obstacles;
    sf::Clock clock;

    sf::Font font;
    sf::Text label;
    bool isGameOver;

    constexpr static float PLAYER_SPEED = 7.f;
    constexpr static float BG_SPEED = 1.5f;
};

#endif
