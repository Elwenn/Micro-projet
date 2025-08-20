#pragma once
#include "Friend.h"
#include <SFML/Graphics.hpp>

class PopCorn : public Friend {

protected:
  float explosionRadius;

public:
    PopCorn(double x, 
      double y,
      float radius,
      const std::string& img = "pop-corn.png",
      float explosionRadius = 200.0f);

    void getHit(Game& game);
    void explode(Game& game);
    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& j) override;


};
