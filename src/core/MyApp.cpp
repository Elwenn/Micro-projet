#include "MyApp.h"
#include "Scene.h"
#include "Game.h"
#include "Scene/EndScreen.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>

MyApp::MyApp() {
    window.create(sf::VideoMode({win_length, win_width}), "Corn War !!!");
    window.setFramerateLimit(30);
}

void MyApp::launch() {
    auto game = Game();
    bool gameInitialized = false;
    sf::Clock gameTimer;
    bool gameEnded = true;
    EndScreen endScreen;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (title_screen.isActive()) {
                title_screen.handleEvent(event, window);

                if (title_screen.isStartClicked()) {
                    title_screen.setActive(false);
                    game.reset();
                    gameInitialized = false;
                    gameEnded = false;
                    gameTimer.restart();
                    title_screen.resetStartClicked();
                }
             } else if (endScreen.isActive()) {
                endScreen.handleEvent(event, window);

                if (endScreen.isRestartClicked()) {
                    endScreen.setActive(false);
                    game.reset();
                    gameInitialized = false;
                    gameEnded = false;
                    gameTimer.restart();
                    endScreen.resetRestartClicked();
                } else if (endScreen.isTitleClicked()) {
                    endScreen.setActive(false);
                    title_screen.setActive(true);
                    endScreen.resetTitleClicked();
                }
            } else {
                if (event->is<sf::Event::Resized>()) {
                    auto resized = event->getIf<sf::Event::Resized>();
                    sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
                    window.setView(sf::View(visibleArea));
                    game.initCorns(0, window);
                }

                if (event->is<sf::Event::MouseButtonPressed>()) {
                    auto pressed = event->getIf<sf::Event::MouseButtonPressed>();
                    if (pressed->button == sf::Mouse::Button::Left) {
                        sf::Vector2f mousePos = window.mapPixelToCoords(pressed->position);
                        game.processEvents(mousePos);
                    }
                }

                if (event->is<sf::Event::KeyPressed>()) {
                    auto keyEvent = event->getIf<sf::Event::KeyPressed>();
                    if (keyEvent->code == sf::Keyboard::Key::S) {
                        game.saveGame("savegame.json");
                    } else if (keyEvent->code == sf::Keyboard::Key::L) {
                        game.loadGame("savegame.json");
                    }
                }
            }
        }

        window.clear();

        if (title_screen.isActive()) {
            title_screen.draw(window);
        } else if (endScreen.isActive()) {
            endScreen.draw(window);
        } else {
            if (!gameInitialized) {
                game.initCorns(50, window);
                gameInitialized = true;
            }

            if (gameTimer.getElapsedTime().asSeconds() >= 30.0f && !gameEnded) {
                gameEnded = true;
                endScreen.updateScore(game.getScoreValue());
                endScreen.setActive(true);
            }

            if (!gameEnded) {
                game.update();
                game.render(window);
            }
        }

        window.display();
    }
}