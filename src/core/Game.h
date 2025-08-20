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
  const int MAX_CORNS = 50;
  int score;
  sf::Text scoreText;
  sf::Font font;
  std::vector<std::unique_ptr<Corn>> corns;
  const int nb_x;
  const int nb_y;
  Scene background;
  Grid grid;
  float spawnTimer;
  float spawnInterval;
  int maxConcurrentCorns;
  int initialCornsCount;
  int spawnedCornsCount;

public:
  Game(int nb_x = 10, int nb_y = 10);
  void addScore(int points);
  void updateScoreDisplay();
  void draw(sf::RenderWindow& window) const;
  int getScore() const;

  std::vector<std::unique_ptr<Corn>>* getCorns();
  void addCorn(std::unique_ptr<Corn> corn);
  void removeDeadCorns();

  void processEvents(sf::Vector2f mousePos);

  void update();

  void render(sf::RenderWindow& window);

  void saveGame(const std::string &filename);

  void loadGame(const std::string &filename);

  void initCorns(int count, const sf::RenderWindow& window);

  void spawnCorn();

};
  



