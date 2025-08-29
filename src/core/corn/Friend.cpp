#include "Friend.h"
#include "../Game.h"
#include "Enemy.h"
#include <cmath>


Friend::Friend(double x, double y,
               float radius,
               const std::string& img,
               int pv,
               int scoreValue)
    : Corn(x, y, radius, img, pv, scoreValue) {}

void Friend::die(Game &game) {
    Corn::die(game);
    const Grid& grid = game.getGrid();
    int friendRow = -1, friendCol = -1;
    float minDistance = std::numeric_limits<float>::max();
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            sf::Vector2f cellPos = grid.getCellPosition(row, col);
            float distance = std::sqrt(
                std::pow(x - cellPos.x, 2) +
                std::pow(y - cellPos.y, 2)
            );

            if (distance < minDistance) {
                minDistance = distance;
                friendRow = row;
                friendCol = col;
            }
        }
    }
    int directions[8][2] = {
            {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1},           {0, 1},
            {1, -1},  {1, 0},  {1, 1}
    };
    int enemiesCreated = 0;
    for (int i = 0; i < 8 && enemiesCreated < 5; i++) {
        int newRow = friendRow + directions[i][0];
        int newCol = friendCol + directions[i][1];
        if (newRow >= 0 && newRow < 5 && newCol >= 0 && newCol < 5) {
            sf::Vector2f enemyPos = grid.getCellPosition(newRow, newCol);
            auto enemy = std::make_unique<Enemy>(
                enemyPos.x,
                enemyPos.y,
                grid.getRadius(),
                "res/ennemy.png"
                );
            game.addCorn(std::move(enemy), true);
            enemiesCreated++;
        }
    }
    while (enemiesCreated < 5) {
        sf::Vector2f randomPos = grid.getRandomCellPosition();
        auto enemy = std::make_unique<Enemy>(
            randomPos.x,
            randomPos.y,
            grid.getRadius(),
            "res/ennemy.png"
            );
        game.addCorn(std::move(enemy), true);
        enemiesCreated++;
    }
}

