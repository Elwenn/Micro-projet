#include "myMain.h"
#include <cstdlib>

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Scene.h"
#include "MyApp.h"

int myMain() {

  MyApp app;
  app.launch();

  return EXIT_SUCCESS;
}