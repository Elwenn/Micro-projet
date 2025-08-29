#pragma once  
#include <SFML/Graphics.hpp>

#include "Scene/EnumScene.h"
#include "Scene/TitleScreen.h"

class MyApp {
public:
  const unsigned int win_length = 1000;
  const unsigned int win_width = 1000;
  sf::RenderWindow window;
  TitleScreen title_screen;
  GameStatus gameStatus;

  MyApp();
  void launch();

};