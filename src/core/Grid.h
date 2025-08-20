#pragma once
#include <SFML/Graphics.hpp>


class Scene;

class Grid {
private:
    sf::Vector2f position;
    float gridOriginX;
    float gridOriginY;
    float cellSize;
    float spacing;
    float step;
    float radius;
    int rows;
    int cols;
    const Scene* backgroundScene;

public:
    Grid(int rows = 5, int cols = 5);
    void setBackgroundScene(const Scene* scene);
    void calculatePosition();
    void calculatePosition(const sf::RenderWindow& window);
    sf::Vector2f getRandomCellPosition() const;
    float getRadius() const;
};
