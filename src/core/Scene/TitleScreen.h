#pragma once
#include <SFML/Graphics.hpp>
#include "../Button.h"
#include "../Scene.h"

class TitleScreen : public Scene {
private:
    Button startButton;
    bool startClicked;

public:
    TitleScreen();
    void draw(sf::RenderWindow& window);
    void handleEvent(const std::optional<sf::Event> &event, sf::RenderWindow &window);
    static void* startGame();
    bool isStartClicked() const;
    void resetStartClicked();
};
