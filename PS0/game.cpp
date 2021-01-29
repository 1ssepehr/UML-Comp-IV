#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>

#include <ctime>
#include <cstdlib>
#include <cmath>
#include <list>
#include "game.hpp"


Boulder::Boulder():
    sf::Sprite(),
    speed_x(RNG * FALL_TILT_LIMIT),
    speed_y(FALL_MIN_SPEED + (RNG) * (FALL_MAX_SPEED - FALL_MIN_SPEED)),
    speed_r()
{
    if (!texture.loadFromFile("./assets/boulder.png"))
        throw EXIT_FAILURE;
    setTexture(texture);
    setPosition({RNG * SepGame::WIDTH, 0.f});
}

void Boulder::move() { sf::Sprite::move(sf::Vector2f{speed_x, speed_y}); }

SepGame::SepGame()
{
    // Create the main window
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Assignment PS0 - Madani");
    window.setFramerateLimit(60);

    // Load textures
    if (!PlayerTex.loadFromFile("./assets/eagle.png"))
        throw EXIT_FAILURE;
    PlayerTex.setSmooth(true);

    if (!BackgroundTex.loadFromFile("./assets/space.jpeg"))
        throw EXIT_FAILURE;
    BackgroundTex.setSmooth(true);
    BackgroundTex.setRepeated(true);

    if (!BoulderTex.loadFromFile("./assets/boulder.png"))
        throw EXIT_FAILURE;
    BoulderTex.setSmooth(true);

    // Load player sprite
    PlayerSpr.setTexture(PlayerTex);
    PlayerSpr.setPosition({WIDTH * 0.5, HEIGHT * 0.8});

    // Load background sprite
    BackgroundSpr_1.setTexture(BackgroundTex);
    BackgroundSpr_2.setTexture(BackgroundTex);

    BackgroundSpr_1.setPosition({0.f, -BackgroundSpr_2.getGlobalBounds().height});
    BackgroundSpr_2.setPosition({0.f, 0.f});

    // Set up the environment
    std::srand(std::time(nullptr));
    isGameOver = false;

}

void SepGame::load_gameOver()
{
    sf::Font font;
    if (!font.loadFromFile("./assets/Ubuntu-R.ttf"))
        throw EXIT_FAILURE;
    label.setFont(font);
    label.setString("You lost! Game over...\nPress [Enter] to exit...");
    label.setCharacterSize(32);
    label.setFillColor(sf::Color::Red);
    label.setPosition({25, 25});
    gameOver.create(sf::VideoMode(400, 200), "Game Over!");
    gameOver.clear(sf::Color::White);
    gameOver.draw(label);
    gameOver.display();
    while(gameOver.isOpen())
    {
        sf::Event enterKeyEvent;
        while(gameOver.pollEvent(enterKeyEvent))
            if (enterKeyEvent.type == sf::Event::KeyPressed &&
                sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                gameOver.close();
                window.close();
                return;
            }
    }
}

void SepGame::start_game()
{
    sf::Vector2f movement;
    clock.restart();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            movement.x = movement.y = 0;
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    movement.x = -PLAYER_SPEED;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    movement.x = PLAYER_SPEED;

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    movement.y = -PLAYER_SPEED;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    movement.y = PLAYER_SPEED;

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


        // Move Players
        PlayerSpr.move(movement);
        adjust_player();

        // Randomly add boulders
        if (clock.getElapsedTime().asSeconds() >= (1.0 / Boulder::SPAWN_RATE))
        {
            clock.restart();
            Obstacles.push_back(Boulder());
        }

        // Moving boulders
        auto it = Obstacles.begin();
        while (it != Obstacles.end())
        {
            it->move();
            if (it->getPosition().y > HEIGHT)  // Remove out-of-window boulders
                Obstacles.erase(it++);
            else ++it;
        }

        // Collision calculation
        for (auto boulder: Obstacles)
        {
            auto PlayerPos = PlayerSpr.getPosition();
            auto BoulderPos = boulder.getPosition();
            auto PlayerDims = PlayerSpr.getGlobalBounds();
            auto BoudlderDims = boulder.getGlobalBounds();
            if (fabs(PlayerPos.x - BoulderPos.x) < 0.8 * (PlayerDims.width + BoudlderDims.width)/2 &&
                fabs(PlayerPos.y - BoulderPos.y) < 0.8 * (PlayerDims.height + BoudlderDims.height)/2)
            {
                isGameOver = true;
            }
        }

        // Clear / Draw / Display cycle
        if(!isGameOver)
        {
            window.clear(sf::Color::Black);
            window.draw(BackgroundSpr_1);
            window.draw(BackgroundSpr_2);
            window.draw(PlayerSpr);
            for (auto boulder: Obstacles)
                window.draw(boulder);
            window.display();
        } else {
            PlayerSpr.setColor(sf::Color(255, 0, 0));
            load_gameOver();
        }
    }
}

void SepGame::adjust_player()
{
    auto curPosition = PlayerSpr.getPosition();
    auto dims = PlayerSpr.getGlobalBounds();
    if (curPosition.x > WIDTH - dims.width) // Right constraint
        PlayerSpr.setPosition({WIDTH - dims.width, curPosition.y});
    if (curPosition.x < 0) // Left constraint
        PlayerSpr.setPosition({0, curPosition.y});

    if (curPosition.y > HEIGHT - dims.height) // Down constraint
        PlayerSpr.setPosition({curPosition.x, HEIGHT - dims.height});
    if (curPosition.y < HEIGHT * 0.4) // Up constraint
        PlayerSpr.setPosition({curPosition.x, HEIGHT * 0.4});

}

int main()
{
    try {
        SepGame gameInstance;
        gameInstance.start_game();
    } catch (int e) { return EXIT_FAILURE; }
    return EXIT_SUCCESS;
}
