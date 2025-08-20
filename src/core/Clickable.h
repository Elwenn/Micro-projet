#pragma once  
#include <memory>
#include <SFML/Graphics.hpp>

class Clickable {
protected:
  double x;
  double y;
  sf::CircleShape collisionShape;
  float radius;

public:
  Clickable(double x, double y, float radius) :
        x(x), y(y),
        collisionShape(radius),
  radius(radius)
  {
    collisionShape.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
    collisionShape.setFillColor(sf::Color::Transparent);
    collisionShape.setOutlineColor(sf::Color::Transparent);
  }

  virtual ~Clickable() = default;

  bool isClicked(const sf::Vector2i& mousePos) const {
    return collisionShape.getGlobalBounds().contains(
      sf::Vector2f(
        static_cast<float>(mousePos.x),
        static_cast<float>(mousePos.y))
    );
  }

  bool contains(sf::Vector2f point) const {
    return collisionShape.getGlobalBounds().contains(point);
  }

  sf::Vector2f getPosition() const {
    return collisionShape.getPosition();
  }

  void setPosition(float x, float y) {
    collisionShape.setPosition(sf::Vector2f(x, y));
    this->x = x;
    this->y = y;
  }
};