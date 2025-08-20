

#include "Game.h"
#include "corn/Corn.h"
#include <iostream>
#include <algorithm>
#include <fstream>

#include "corn/Enemy.h"
#include "corn/PopCorn.h"

Game::Game(const int nb_x, const int nb_y) :
  score{0},
  nb_x{ nb_x },
  nb_y{ nb_y },
  font{ sf::Font("res/arial.ttf") },
  scoreText{ sf::Text(font) },
  background{ Scene("Back-ground5x5.png") },
  spawnTimer(0.0f),
  spawnInterval(1.5f),
  maxConcurrentCorns(10),
  initialCornsCount(50),
  spawnedCornsCount(0),
  grid()

{
  scoreText.setFont(font);
  scoreText.setCharacterSize(30);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition(sf::Vector2f(10.f, 10.f));
  updateScoreDisplay();
  grid.setBackgroundScene(&background);
  std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Game::initCorns(int count, const sf::RenderWindow& window) {
  background.calculatePosition(window);
  grid.calculatePosition();

  initialCornsCount = count;
  spawnedCornsCount = 0;
}
void Game::spawnCorn() {
  if (corns.size() >= maxConcurrentCorns || spawnedCornsCount >= initialCornsCount) {
    return;
  }

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
    case 2: // PopCorn
      corn = std::make_unique<PopCorn>(position.x, position.y, radius, "res/pop-corn.png", 200.0f);
      break;
  }

  if (corn) {
    addCorn(std::move(corn));
    spawnedCornsCount++;
  }
}

void Game::addScore(int points) {
  score += points;
  updateScoreDisplay();
}

void Game::updateScoreDisplay() {
  scoreText.setString("Score: " + std::to_string(score));
}

void Game::draw(sf::RenderWindow& window) const {
  //background.display(&window);
  window.draw(scoreText);
}

std::vector<std::unique_ptr<Corn>>* Game::getCorns() {
  return &corns;
}

void Game::addCorn(std::unique_ptr<Corn> corn) {
  if (corns.size() < MAX_CORNS) {
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

int Game::getScore() const {
  return score;
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

  spawnTimer+=1.0f /30.0f;
  if (spawnTimer >= spawnInterval) {
    spawnTimer =0.0f;
    spawnCorn();
  }

  if (corns.empty() && spawnedCornsCount >= initialCornsCount) {
    spawnedCornsCount = 0;
  }
}

void Game::render(sf::RenderWindow& window) {
  window.clear();
  background.display(&window);

  // Dessiner tous les corns
  for (const auto& corn : corns) {
    corn->draw(window);
  }

  window.draw(scoreText);
  window.display();
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
      } else if (type == "PopCorn") {
        corn = std::make_unique<PopCorn>(0, 0, 20.f, "/res/pop-corn.png");
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


//TODO : Initialize the corns

/*
void Game::run() {

  
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  while (mWindow.isOpen()) {
    sf::Time elapsedTime = clock.restart();
    timeSinceLastUpdate += elapsedTime;
    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;

      processEvents();
      update(TimePerFrame);
    }

    updateStatistics(elapsedTime);
    render();
  }
  

}

void Game::processEvents() {

  
  while (const std::optional event = mWindow.pollEvent()) {
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      mTarget.handlePlayerInput(keyPressed->code, true);
    }
    else if (const auto* keyReleased =
      event->getIf<sf::Event::KeyReleased>()) {
      mTarget.handlePlayerInput(keyReleased->code, false);
    }
    else if (event->is<sf::Event::Closed>()) {
      mWindow.close();
    }
  }

  
}

void Game::update(const sf::Time elapsedTime) { 
  
  mTarget.update(elapsedTime);
  
  }

void Game::render() {
  
  mWindow.clear();
  mTarget.drawCurrent(mWindow);
  mWindow.draw(mStatisticsText);
  mWindow.display();
  
}
*/
