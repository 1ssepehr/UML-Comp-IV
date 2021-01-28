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

class Boulder: public sf::Sprite
{
public:
    Boulder();
    void move();
private:
    sf::Texture texture;
    float speed_x;
    float speed_y;
};

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
    sf::Sprite PlayerSpr;
    sf::Texture PlayerTex;
    sf::Texture BackgroundTex;
    sf::Texture BoulderTex;
    std::list<Boulder> Obstacles;
    sf::Clock clock;

    sf::Font font;
    sf::Text label;
    bool isGameOver;
};

constexpr int WINDOW_WIDTH = 960;
constexpr int WINDOW_HEIGHT = 800;
constexpr float PLAYER_SPEED = 7.f;
constexpr float BOULDERING_RATE = 5.0;
constexpr float BOULDER_SPEED_MIN = 3.f;
constexpr float BOULDER_SPEED_MAX = 12.f;
constexpr float BOULDER_HORIZONTAL_MAX_SPEED = 1.f;

#endif