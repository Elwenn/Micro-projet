#pragma once
#include "Clickable.h"
#include "TextureManager.h"
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

class Game;
class Corn : public Clickable {
protected:
    std::string imgPath;
    int pv;
    int scoreValue;
    int countDown;
    bool alive;
    sf::Sprite sprite;

public:
    explicit Corn(double x, double y,
         float radius,
         const std::string& imgPath,
         int pv = 3,
         int scoreValue = 10);

    void getHit(Game &game);
    void act();
    void draw(sf::RenderWindow& window) const;
    virtual void die(Game& game);
    bool isAlive() const;
    bool contains(sf::Vector2f point) const ;
    int getPV() const;
    virtual nlohmann::json toJson() const ;
    virtual void fromJson(const nlohmann::json& j);
};