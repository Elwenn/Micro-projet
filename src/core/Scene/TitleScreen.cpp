#include "TitleScreen.h"
#include <iostream>
#include "../TextureManager.h"

TitleScreen::TitleScreen() :
Scene("Title_screen.png"),
startButton("Start Game", sf::Vector2f(400, 500), sf::Vector2f(200, 50)),
active(true),
startClicked(false) {
    startButton.setOnClick([this]() {
        this->startClicked = true;
    });
}

void TitleScreen::draw(sf::RenderWindow& window) {
    if (!active) return;
    Scene::display(&window);
    startButton.draw(window);
}

void TitleScreen::handleEvent(const std::optional<sf::Event>& event, sf::RenderWindow& window) {
    if (!active) return;

    startButton.handleEvent(event, window);
}

bool TitleScreen::isActive() const {
    return active;
}

void TitleScreen::setActive(bool active) {
    this->active = active;
}

bool TitleScreen::isStartClicked() const {
    return startClicked;
}

void TitleScreen::resetStartClicked() {
    startClicked = false;
}
