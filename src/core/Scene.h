#pragma once
#include <SFML/Graphics.hpp>

class Scene {

private:
  sf::Texture background;
  sf::Vector2f position;
  sf::Vector2u textureSize;

public:
  Scene() = default;
  Scene(const std::string image);
  void display(sf::RenderWindow* window);
  void calculatePosition(const sf::RenderWindow& window);
  sf::Vector2f getPosition() const { return position; }
  sf::Vector2u getTextureSize() const { return textureSize; }
};
