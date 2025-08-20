#pragma once
#include "Corn.h"

class Enemy : public Corn {
public:
    Enemy(double x, double y,
          float radius,
          const std::string& img ="ennemy.png",
          int pv = 1
          ,
          int scoreValue = 20) ;

};