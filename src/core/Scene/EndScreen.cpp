#include "EndScreen.h"
#include <iostream>
#include "../TextureManager.h"

EndScreen::EndScreen(sf::Text scoretext) :
Scene("Title_screen.png"),
active(true),
scoreText(scoretext),
restartButton("Re-Start Game", sf::Vector2f(400, 500), sf::Vector2f(200, 50)),
restartClicked(false),
TitleButton("Title Screen", sf::Vector2f(400, 400), sf::Vector2f(200, 50)),
TitleClicked(false)
{
    restartButton.setOnClick([this]() {
        this->restartClicked = true;
    });
    TitleButton.setOnClick([this]() {
        this->TitleClicked = true;
    });
}

void EndScreen::draw(sf::RenderWindow& window) {
    if (!active) return;
    Scene::display(&window);
    restartButton.draw(window);
    TitleButton.draw(window);
    window.draw(scoreText);

}
bool EndScreen::isActive() const {
    return active;
}

void EndScreen::setActive(bool active) {
    this->active = active;
}

void EndScreen::handleEvent(const std::optional<sf::Event>& event, sf::RenderWindow& window) {
    if (!active) return;

    restartButton.handleEvent(event, window);
    TitleButton.handleEvent(event, window);
}

bool EndScreen::isRestartClicked() const {
    return restartClicked;
}

void EndScreen::resetRestartClicked() {
    restartClicked = false;
}

bool EndScreen::isTitleClicked() const {
    return TitleClicked;
}

void EndScreen::resetTitleClicked() {
    TitleClicked = false;
}