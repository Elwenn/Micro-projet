add_library(lib_core
  myMain.cpp
  myMain.h
 "Game.h" "Game.cpp" "Scene.h" "Scene.cpp" "Clickable.h" "Clickable.cpp" "corn/Corn.h" "corn/Corn.cpp" "Button.h" "Button.cpp" "MyApp.h" "MyApp.cpp" "corn/Friend.h" "corn/Friend.cpp" "corn/Enemy.h" "corn/Enemy.cpp"
        TextureManager.h
        TextureManager.cpp
        Grid.h
        Grid.cpp
        Scene/TitleScreen.h
        Scene/TitleScreen.cpp
        Scene/EndScreen.h
        Scene/EndScreen.cpp
        Scene/EnumScene.h)
target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC pugixml sfml-graphics sfml-window sfml-system nlohmann_json::nlohmann_json)
