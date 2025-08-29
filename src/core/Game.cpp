

#include "Game.h"
#include "corn/Corn.h"
#include <iostream>
#include <algorithm>
#include <fstream>

#include "corn/Enemy.h"
#include "corn/Friend.h"

Game::Game(const sf::RenderWindow& window) :
  score{0},
  font{ sf::Font("res/arial.ttf") },
  scoreText{ sf::Text(font) },
  background{ Scene("Back-ground5x5.png") },
minCornsOnScreen(5),
 maxCornsOnScreen(10),
 framesSinceLastSpawn(0),
 spawnCooldownFrames(30),
  maxConcurrentCorns(10),
  initialCornsCount(50),
  grid()

{
  scoreText.setFont(font);
  scoreText.setCharacterSize(30);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition(sf::Vector2f(10.f, 10.f));
  updateScoreDisplay();
  grid.setBackgroundScene(&background);
  std::srand(static_cast<unsigned>(std::time(nullptr)));
  background.calculatePosition(window);
  grid.calculatePosition();

  for (int i = 0; i < std::min(initialCornsCount, maxConcurrentCorns); i++) {
    spawnCorn();
  }
}

void Game::spawnCorn() {
  sf::Vector2f position = grid.getRandomCellPosition();
  float radius = grid.getRadius();

  int type = std::rand() % 3;
  std::unique_ptr<Corn> corn;

  switch (type) {
    case 0: // Enemy
      corn = std::make_unique<Enemy>(position.x, position.y, radius, "res/ennemy.png");
      break;
    case 1: // Friend
      corn = std::make_unique<Friend>(position.x, position.y, radius, "res/friend.png");
      break;
  }

  if (corn) {
    addCorn(std::move(corn));
  }
}

void Game::addScore(int points) {
  score += points;
  updateScoreDisplay();
}

void Game::updateScoreDisplay() {
  scoreText.setString("Score: " + std::to_string(score));
}

void Game::drawScore(sf::RenderWindow& window) const {
  window.draw(scoreText);
}


void Game::addCorn(std::unique_ptr<Corn> corn) {
  if (corns.size() < maxCornsOnScreen) {
    corns.push_back(std::move(corn));
  }
}

void Game::removeDeadCorns() {
  // Supprimer les corns qui ne sont plus vivants
  corns.erase(std::remove_if(corns.begin(), corns.end(),
      [](const std::unique_ptr<Corn>& c) {
          return !c->isAlive();
      }),
  corns.end());
}

 sf::Text Game::getScore() {
  return scoreText;
}

void Game::processEvents(sf::Vector2f mousePos) {
  for (auto& corn : corns) {
    if (corn->isAlive() && corn->contains(mousePos)) {
      corn->getHit(*this);
    }
  }
}

void Game::update() {
  for (auto& corn : corns) {
    corn->act();
  }
  removeDeadCorns();

  framesSinceLastSpawn++;

  if (corns.size() < minCornsOnScreen && framesSinceLastSpawn >= spawnCooldownFrames) {
    spawnCorn();
    framesSinceLastSpawn = 0;
  }

  else if (corns.size() < maxCornsOnScreen && framesSinceLastSpawn >= spawnCooldownFrames * 2) {
    spawnCorn();
    framesSinceLastSpawn = 0;
  }

  if (corns.empty()) {
    for (int i = 0; i < minCornsOnScreen; i++) {
      spawnCorn();
    }
  }
}

void Game::render(sf::RenderWindow& window) {
  background.display(&window);

  // Dessiner tous les corns
  for (const auto& corn : corns) {
    corn->draw(window);
  }

  window.draw(scoreText);
}

void Game::saveGame(const std::string& filename) {
  nlohmann::json gameState;
  gameState["score"] = score;

  nlohmann::json cornsArray;
  for (auto& corn : corns) {
    cornsArray.push_back(corn->toJson());
  }
  gameState["corns"] = cornsArray;

  std::ofstream file(filename);
  if (file) {
    file << gameState.dump(4);
  } else {
    std::cerr << "Failed to save game: " << filename << std::endl;
  }
}

void Game::loadGame(const std::string& filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Failed to load game: " << filename << std::endl;
    return;
  }

  try {
    nlohmann::json gameState;
    file >> gameState;

    score = gameState["score"];
    updateScoreDisplay();

    corns.clear();
    for (auto& cornJson : gameState["corns"]) {
      std::string type = cornJson["type"];
      std::unique_ptr<Corn> corn;
      auto shape = std::make_unique<sf::CircleShape>(25.f);

      if (type == "Friend") {
        corn = std::make_unique<Friend>(0, 0, 20.f,"res/friend.png");
      } else if (type == "Enemy") {
        corn = std::make_unique<Enemy>(0, 0, 20.f, "/res/enemy.png");
      } else {
        corn = std::make_unique<Corn>(0, 0, 20.F, "");
      }

      corn->fromJson(cornJson);
      corns.push_back(std::move(corn));
    }
  } catch (const std::exception& e) {
    std::cerr << "Error loading game: " << e.what() << std::endl;
  }
}

int Game::getScoreValue() const {
  return score;
}
