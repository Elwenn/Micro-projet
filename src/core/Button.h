#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "Clickable.h"

class Button : public Clickable {
private:
    sf::Text text;
    sf::Font font;
    std::function<void()> onClick;
    sf::RectangleShape visualShape;

public:
    Button(const std::string& btnText, sf::Vector2f position, sf::Vector2f size);
    void setOnClick(std::function<void()> func);
    void draw(sf::RenderWindow& window) const;
    void handleEvent(const std::optional<sf::Event>& event, sf::RenderWindow& window);

    bool contains(sf::Vector2f point) const override {
        return visualShape.getGlobalBounds().contains(point);
    }
};