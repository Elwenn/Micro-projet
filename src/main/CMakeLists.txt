add_executable(main
  main.cpp
        ../core/TextureManager.h
        ../core/TextureManager.cpp
        ../core/Grid.h
        ../core/Grid.cpp
)

target_link_libraries(main PUBLIC lib_core pugixml sfml-graphics sfml-window sfml-system nlohmann_json::nlohmann_json)

add_custom_target(copy-res ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/res)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/res
                   DEPENDS ${CMAKE_SOURCE_DIR}/res
                   COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
                           ${CMAKE_SOURCE_DIR}/res
                           ${CMAKE_CURRENT_BINARY_DIR}/res)
add_dependencies(main copy-res)
add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:main>/res)
