#pragma once
#include "Corn.h"

class Friend : public Corn {
public:
    Friend(double x, double y,
           float radius,
           const std::string& img ="friend.png",
           int pv = 2,
           int scoreValue = -10);
    void die(Game& game);
};
