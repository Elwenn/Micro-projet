#pragma once  
#include <SFML/Graphics.hpp>

class MyApp {
public:
  const unsigned int win_length = 1000;
  const unsigned int win_width = 1000;
  sf::RenderWindow window;

  MyApp();
  void launch();

};