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
    speed_x((std::rand() % 100) / 100.0 * BOULDER_HORIZONTAL_MAX_SPEED),
    speed_y(BOULDER_SPEED_MIN + ((std::rand() % 100) / 100.0) * (BOULDER_SPEED_MAX - BOULDER_SPEED_MIN))
{
    if (!texture.loadFromFile("./assets/ball.png"))
        throw EXIT_FAILURE;
    setTexture(texture);
    setPosition({static_cast<float>(std::rand() % WINDOW_WIDTH), 0});
}

void Boulder::move() { sf::Sprite::move(sf::Vector2f{speed_x, speed_y}); }

SepGame::SepGame()
{
    // Create the main window
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Assignment PS0 - Madani");
    window.setFramerateLimit(60);

    // Load textures
    if (!PlayerTex.loadFromFile("./assets/eagle.png"))
        throw EXIT_FAILURE;
    PlayerTex.setSmooth(true);

    if (!BackgroundTex.loadFromFile("./assets/space.jpeg"))
        throw EXIT_FAILURE;
    BackgroundTex.setSmooth(true);
    BackgroundTex.setRepeated(true);

    if (!BoulderTex.loadFromFile("./assets/ball.png"))
        throw EXIT_FAILURE;
    BoulderTex.setSmooth(true);
    
    // Load player sprite
    PlayerSpr.setTexture(PlayerTex);
    PlayerSpr.setPosition({WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.8});

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

        // Moving Playerss
        PlayerSpr.move(movement);
        adjust_player();

        // Randomly add boulders
        if (clock.getElapsedTime().asSeconds() >= (1.0 / BOULDERING_RATE))
        {
            clock.restart();
            Obstacles.push_back(Boulder());
        }
        
        // Moving boulders
        auto it = Obstacles.begin();
        while (it != Obstacles.end())
        {
            it->move();
            if (it->getPosition().y > WINDOW_HEIGHT)  // Remove out-of-window boulders
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
    if (curPosition.x > WINDOW_WIDTH - dims.width) // Right constraint
        PlayerSpr.setPosition({WINDOW_WIDTH - dims.width, curPosition.y});
    if (curPosition.x < 0) // Left constraint
        PlayerSpr.setPosition({0, curPosition.y});

    if (curPosition.y > WINDOW_HEIGHT - dims.height) // Down constraint
        PlayerSpr.setPosition({curPosition.x, WINDOW_HEIGHT - dims.height});
    if (curPosition.y < WINDOW_HEIGHT * 0.4) // Up constraint
        PlayerSpr.setPosition({curPosition.x, WINDOW_HEIGHT * 0.4});

}

int main()
{
    try {
        SepGame gameInstance;
        gameInstance.start_game();
    } catch (int e) { return EXIT_FAILURE; } 
    return EXIT_SUCCESS;
}