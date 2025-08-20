#pragma once
#include <SFML/Graphics.hpp>
#include "../Button.h"
#include "../Scene.h"

class TitleScreen : public Scene {
private:
    Button startButton;
    bool active;
    bool startClicked;

public:
    TitleScreen();
    void draw(sf::RenderWindow& window);
    void handleEvent(const std::optional<sf::Event> &event, sf::RenderWindow &window);
    bool isActive() const;
    void setActive(bool active);
    static void* startGame();
    bool isStartClicked() const;
    void resetStartClicked();
};
