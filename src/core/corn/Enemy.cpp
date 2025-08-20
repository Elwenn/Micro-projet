#include "Corn.h"
#include "Enemy.h"

Enemy::Enemy(double x, double y,
  float radius,
  const std::string& img,
  int pv,
  int scoreValue) :
  Corn(x, y, radius, img, pv, scoreValue) {
    countDown = 15 + (std::rand() % 76);
}
