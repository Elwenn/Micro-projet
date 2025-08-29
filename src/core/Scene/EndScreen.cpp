#include "EndScreen.h"
#include <iostream>
#include "../TextureManager.h"

EndScreen::EndScreen() :
Scene("End_screen.png"),
font{ sf::Font("res/arial.ttf") },
endscoreText{ sf::Text(font) },
restartButton("Re-Start Game", sf::Vector2f(400, 500), sf::Vector2f(200, 50)),
restartClicked(false),
TitleButton("Title Screen", sf::Vector2f(400, 400), sf::Vector2f(200, 50)),
TitleClicked(false)
{
    endscoreText.setFont(font);
    endscoreText.setCharacterSize(30);
    endscoreText.setFillColor(sf::Color::White);
    endscoreText.setPosition(sf::Vector2f(10.f, 10.f));

    sf::FloatRect textRect = endscoreText.getLocalBounds();
    endscoreText.setOrigin(textRect.getCenter());
    endscoreText.setPosition(sf::Vector2f(500, 300));

    restartButton.setOnClick([this]() {
        this->restartClicked = true;
    });
    TitleButton.setOnClick([this]() {
        this->TitleClicked = true;
    });
}

void EndScreen::updateScore(int score) {
    endscoreText.setString("Score: " + std::to_string(score));

    sf::FloatRect textRect = endscoreText.getLocalBounds();
    endscoreText.setOrigin(textRect.getCenter());
    endscoreText.setPosition(sf::Vector2f(500, 300));
}

void EndScreen::draw(sf::RenderWindow& window) {
    Scene::display(&window);
    restartButton.draw(window);
    TitleButton.draw(window);
    window.draw(endscoreText);

}


void EndScreen::handleEvent(const std::optional<sf::Event>& event, sf::RenderWindow& window) {
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