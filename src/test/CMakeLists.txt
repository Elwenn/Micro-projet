#
# Lines inspired by https://google.github.io/googletest/quickstart-cmake.html
#

# Note: include(GoogleTest) and enable_testing() already done in top CMakeLists.txt

add_executable(unitTests
  unitTests.cpp
        ../core/TextureManager.h
        ../core/TextureManager.cpp
        ../core/Grid.h
        ../core/Grid.cpp
        ../core/Scene/EndScreen.h
)
target_link_libraries(unitTests GTest::gtest_main lib_core pugixml sfml-graphics nlohmann_json::nlohmann_json)

# D�couverte automatique des tests avec GoogleTest
include(GoogleTest)
gtest_discover_tests(unitTests)

# ?? Copie du dossier `res/` pour les ressources (comme arial.ttf)
file(GLOB RESOURCES_FOR_TEST CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/res/*.*)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/res/arial.ttf
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/res
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          ${RESOURCES_FOR_TEST}
          ${CMAKE_CURRENT_BINARY_DIR}/res
  DEPENDS ${RESOURCES_FOR_TEST}
  COMMENT "Copying resource files to build/test/res"
)

# La target `copy-resources-for-test` d�pend du fichier copi�
add_custom_target(copy-resources-for-test ALL
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/res/arial.ttf
)

# On s'assure que les ressources sont copi�es avant d'ex�cuter les tests
add_dependencies(unitTests copy-resources-for-test)