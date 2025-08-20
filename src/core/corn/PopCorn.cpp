#include "PopCorn.h"
#include "Game.h"
#include "Enemy.h"
#include <cmath>

PopCorn::PopCorn(double x, double y,
                 float radius,
                 const std::string& img,
                 float explosionRadius) : 
    Friend(x, y, radius, img),
    explosionRadius{ explosionRadius } 
{}


void PopCorn::getHit(Game& game) {
  if (!isAlive()) {
    return;
  }
  
  explode(game);
  alive = false;
}


void PopCorn::explode(Game& game){
  
  sf::Vector2f popPos = getPosition();
  for (auto& corn : *game.getCorns()) {
        Enemy* enemy = dynamic_cast<Enemy*>(corn.get());
        if (enemy && enemy->isAlive()) {
            sf::Vector2f enemyPos = enemy->getPosition();
            float dx = enemyPos.x - popPos.x;
            float dy = enemyPos.y - popPos.y;
            float distance = std::sqrt(dx*dx + dy*dy);

            if (distance <= explosionRadius) {
                enemy->takeDamage(enemy->getPV());
                game.addScore(enemy->getScoreValue());
            }
        }
    }
}

nlohmann::json PopCorn::toJson() const {
    auto j = Friend::toJson();
    j["type"] = "PopCorn";
    j["explosionRadius"] = explosionRadius;
    return j;
}

void PopCorn::fromJson(const nlohmann::json& j) {
    Friend::fromJson(j);
    explosionRadius = j["explosionRadius"];
}
