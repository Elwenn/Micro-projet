#include "Grid.h"
#include "Scene.h"

Grid::Grid(int rows, int cols) :
    gridOriginX(131.0f),
    gridOriginY(131.0f),
    cellSize(147.0f),
    spacing(10.0f),
    step(cellSize + spacing),
    radius(cellSize * 0.4f),
    rows(rows),
    cols(cols),
backgroundScene(nullptr)
{
    position = sf::Vector2f(0, 0);
}

void Grid::setBackgroundScene(const Scene* scene) {
    backgroundScene = scene;
}

void Grid::calculatePosition() {
    if (backgroundScene) {
        position = backgroundScene->getPosition();
    }
}

sf::Vector2f Grid::getRandomCellPosition() const {
    int row = std::rand() % rows;
    int col = std::rand() % cols;

    float x = position.x + gridOriginX + col * step;
    float y = position.y + gridOriginY + row * step;

    return sf::Vector2f(x, y);
}

float Grid::getRadius() const {
    return radius;
}