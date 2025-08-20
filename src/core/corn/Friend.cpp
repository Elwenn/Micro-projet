#include "Friend.h"
#include "../Game.h"

Friend::Friend(double x, double y,
               float radius,
               const std::string& img,
               int pv,
               int scoreValue)
    : Corn(x, y, radius, img, pv, scoreValue) {}

