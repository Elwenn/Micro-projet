#include "MyApp.h"
#include "Scene.h"
#include "Game.h"
#include <SFML/Window/Keyboard.hpp>

MyApp::MyApp() {
    window.create(sf::VideoMode({win_length, win_width}), "Corn Game !!!");
    window.setFramerateLimit(30);
}

void MyApp::launch() {
    auto game = Game();
    game.initCorns(50, window);

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* resized = event->getIf<sf::Event::Resized>()) {
                sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
                window.setView(sf::View(visibleArea));

                game.initCorns(0, window);
            }

            if (const auto* pressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2f mousePos = window.mapPixelToCoords(
                    {pressed->position.x, pressed->position.y}
                );
                game.processEvents(mousePos);
            }

            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->code == sf::Keyboard::Key::S) {
                    game.saveGame("savegame.json");
                } else if (keyEvent->code == sf::Keyboard::Key::L) {
                    game.loadGame("savegame.json");
                }
            }
        }

        game.update();
        window.clear();
        game.render(window);
        window.display();
    }
}