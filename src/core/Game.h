#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include "corn/Corn.h"
#include "Scene.h"
#include "Grid.h"

class Game {
private:
  int score;
  sf::Text scoreText;
  sf::Font font;
  std::vector<std::unique_ptr<Corn>> corns;
  Scene background;
  Grid grid;
  int minCornsOnScreen;
  int maxCornsOnScreen;
  int framesSinceLastSpawn;
  int spawnCooldownFrames;
  int maxConcurrentCorns;
  int initialCornsCount;

public:
  Game(const sf::RenderWindow& window);
  void addScore(int points);
  void updateScoreDisplay();
  void drawScore(sf::RenderWindow& window) const;
  sf::Text getScore();
  void addCorn(std::unique_ptr<Corn> corn);
  void removeDeadCorns();
  void processEvents(sf::Vector2f mousePos);
  void update();
  void render(sf::RenderWindow& window);
  void saveGame(const std::string &filename);
  void loadGame(const std::string &filename);
  void spawnCorn();
  int getScoreValue() const;
};
  



