#pragma once
#include <SFML/Graphics.hpp>
#include "../Scene.h"
#include "../Game.h"
#include "../Button.h"

class EndScreen : public Scene {
private:
    bool active;
    sf::Text scoreText;
    Button restartButton;
    bool restartClicked;
    Button TitleButton;
    bool TitleClicked;

public:
    EndScreen(sf::Text scoretext);
    void draw(sf::RenderWindow& window);
    bool isActive() const;
    void setActive(bool active);
    void handleEvent(const std::optional<sf::Event> &event, sf::RenderWindow &window);
    static void* restartGame();
    static void* TitleScreen();
    bool isRestartClicked() const;
    void resetRestartClicked();
    bool isTitleClicked() const;
    void resetTitleClicked();
};
