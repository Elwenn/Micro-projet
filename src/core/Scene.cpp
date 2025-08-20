#include "Scene.h"

#include <iostream>

Scene::Scene(const std::string image){
  sf::Texture t;
  if (!t.loadFromFile("res/" + image)) {
    std::cerr << "Failed to load texture" << image<< std::endl;
  };
  background = t;
}


void Scene::display(sf::RenderWindow* window) {
  if (background.getSize().x == 0) return;

  sf::Sprite sprite(background);
  sf::Vector2u windowSize = window->getSize();
  sf::Vector2u textureSize = background.getSize();


  float posX = (windowSize.x - textureSize.x) / 2.0f;
  float posY = (windowSize.y - textureSize.y) / 2.0f;

  sprite.setPosition(sf::Vector2f(posX, posY));
  window->draw(sprite);
}


void Scene::calculatePosition(const sf::RenderWindow& window) {
  if (textureSize.x == 0 || textureSize.y == 0) return;

  sf::Vector2u windowSize = window.getSize();
  position.x = (windowSize.x - textureSize.x) / 2.0f;
  position.y = (windowSize.y - textureSize.y) / 2.0f;
}