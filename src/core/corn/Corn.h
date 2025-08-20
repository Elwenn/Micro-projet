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
    void die(Game& game);

    bool isAlive() const;
    int getPV() const;
    int getScoreValue() const;
    void takeDamage(int damage);

    bool contains(sf::Vector2f point) const ;

    const sf::Sprite* getShape() const;

    virtual nlohmann::json toJson() const ;
    virtual void fromJson(const nlohmann::json& j);
};