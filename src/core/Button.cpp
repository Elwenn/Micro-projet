#include "Button.h"
#include <iostream>

Button::Button(const std::string& btnText, sf::Vector2f position, sf::Vector2f size) : Clickable(position.x, position.y,
    std::min(size.x, size.y) / 2.0f), text(font, btnText, 24) {
    visualShape.setPosition(position);
    visualShape.setSize(size);
    visualShape.setFillColor(sf::Color(70, 70, 70, 200));
    visualShape.setOutlineThickness(2);
    visualShape.setOutlineColor(sf::Color::White);

    if (!font.openFromFile("res/arial.ttf")) {
        std::cerr << "Failed to load font for button" << std::endl;
    }

    text.setFont(font);
    text.setString(btnText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.getCenter());
    text.setPosition(sf::Vector2f(position.x + size.x / 2.0f, position.y + size.y / 2.0f));
}

void Button::setOnClick(std::function<void()> func) {
    onClick = func;
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(visualShape);
    window.draw(text);
}

void Button::handleEvent(const std::optional<sf::Event>& event, sf::RenderWindow& window) {
    if (event && event->is<sf::Event::MouseButtonPressed>()) {
        auto pressed = event->getIf<sf::Event::MouseButtonPressed>();
        if (pressed && pressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(pressed->position);
            if (contains(mousePos) && onClick) {
                onClick();
            }
        }
    }

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (contains(mousePos)) {
        visualShape.setFillColor(sf::Color(100, 100, 100, 220));
    } else {
        visualShape.setFillColor(sf::Color(70, 70, 70, 200));
    }
}
