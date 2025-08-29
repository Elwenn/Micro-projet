#include "Corn.h"
#include "../Game.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <random>

Corn::Corn(double x, double y,
           float radius,
           const std::string& imgPath,
           int pv,
           int scoreValue) : Clickable{x, y, radius},
                             imgPath(imgPath),
                             pv(pv),
                             scoreValue(scoreValue),
                             countDown(10 + (std::rand() % 91)), alive(true),
                             sprite(TextureManager::getTexture(imgPath)) {
    const sf::Texture &texture = TextureManager::getTexture(imgPath);
    sprite.setTexture(texture);

    sprite.setPosition(sf::Vector2f(
        static_cast<float>(x),
        static_cast<float>(y)
    ));

    sf::Vector2u textureSize = texture.getSize();
    float scaleX = radius * 2 / textureSize.x;
    float scaleY = radius * 2 / textureSize.y;
    sprite.setScale(sf::Vector2f(scaleX, scaleY));
}

void Corn::getHit(Game &game) {
    if (!alive) return;

    pv--;
    if (pv <= 0) {
        die(game);
    } else {
        countDown = 100;
    }
}

void Corn::die(Game &game) {
    game.addScore(scoreValue);
    alive =false;
}

void Corn::act() {
    if (!alive) return;
    countDown--;
    if (countDown <= 0) alive = false;
}

void Corn::draw(sf::RenderWindow& window) const {
    if (alive) {
        window.draw(sprite);
    }
}
bool Corn::isAlive() const { return alive; }
int Corn::getPV() const {
    return pv;
}


nlohmann::json Corn::toJson() const {
    return {
            {"x", x},
            {"y", y},
            {"radius", radius},  // Rayon ajouté
            {"imgPath", imgPath},
            {"pv", pv},
            {"scoreValue", scoreValue},
            {"countDown", countDown},
            {"alive", alive},
            {"type", "Corn"}
    };
}



void Corn::fromJson(const nlohmann::json& j) {
    x = j["x"];
    y = j["y"];
    radius = j["radius"];
    imgPath = j["imgPath"];
    pv = j["pv"];
    scoreValue = j["scoreValue"];
    countDown = j["countDown"];
    alive = j["alive"];


    const sf::Texture& texture = TextureManager::getTexture(imgPath);
    sprite.setTexture(texture);

    sprite.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
    sf::Vector2u textureSize = texture.getSize();
    float scaleX = radius * 2 / textureSize.x;
    float scaleY = radius * 2 / textureSize.y;
    sprite.setScale(sf::Vector2f(scaleX, scaleY));
}


bool Corn::contains(sf::Vector2f point) const {

    float centerX = x + radius;
    float centerY = y + radius;
    float dx = point.x - centerX;
    float dy = point.y - centerY;
    return (dx * dx + dy * dy) <= (radius * radius);
}