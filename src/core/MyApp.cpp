#include "MyApp.h"
#include "Scene.h"
#include "Game.h"
#include "Scene/EndScreen.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>

MyApp::MyApp() {
    window.create(sf::VideoMode({win_length, win_width}), "Corn War !!!");
    window.setFramerateLimit(30);
    gameStatus = GameStatus::TitleScreen;
}

void MyApp::launch() {
    std::unique_ptr<Game> game =nullptr;
    sf::Clock gameTimer;
    EndScreen endScreen;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (gameStatus == GameStatus::TitleScreen) {
                title_screen.handleEvent(event, window);

                if (title_screen.isStartClicked()) {
                    gameStatus = GameStatus::GameScreen;
                    game = std::make_unique<Game>(window);
                    gameTimer.restart();
                    title_screen.resetStartClicked();
                }
             } else if (gameStatus == GameStatus::EndScreen) {
                endScreen.handleEvent(event, window);

                if (endScreen.isRestartClicked()) {
                    gameStatus = GameStatus::GameScreen;
                    game = std::make_unique<Game>(window);
                    gameTimer.restart();
                    endScreen.resetRestartClicked();
                } else if (endScreen.isTitleClicked()) {
                    gameStatus = GameStatus::TitleScreen;
                    endScreen.resetTitleClicked();
                }
            } else {
                if (event->is<sf::Event::Resized>()) {
                    auto resized = event->getIf<sf::Event::Resized>();
                    sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
                    window.setView(sf::View(visibleArea));
                }

                if (event->is<sf::Event::MouseButtonPressed>()) {
                    auto pressed = event->getIf<sf::Event::MouseButtonPressed>();
                    if (pressed->button == sf::Mouse::Button::Left) {
                        sf::Vector2f mousePos = window.mapPixelToCoords(pressed->position);
                        game->processEvents(mousePos);
                    }
                }

                if (event->is<sf::Event::KeyPressed>()) {
                    auto keyEvent = event->getIf<sf::Event::KeyPressed>();
                    if (keyEvent->code == sf::Keyboard::Key::S) {
                        game->saveGame("savegame.json");
                    } else if (keyEvent->code == sf::Keyboard::Key::L) {
                        game->loadGame("savegame.json");
                    }
                }
            }
        }

        window.clear();

        if (gameStatus == GameStatus::TitleScreen) {
            title_screen.draw(window);
        } else if (gameStatus == GameStatus::EndScreen) {
            endScreen.draw(window);
        } else if (gameStatus == GameStatus::GameScreen) {


            if (gameTimer.getElapsedTime().asSeconds() >= 30.0f ) {
                endScreen.updateScore(game->getScoreValue());
                gameStatus = GameStatus::EndScreen;
            } else {
                game->update();
                game->render(window);
            }
        }

        window.display();
    }
}