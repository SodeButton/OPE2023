cmake_minimum_required(VERSION 3.26)
project(OPE2023)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "cmake-build-debug/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_TTF_DIRS})
include_directories(${SDL2_INCLUDE_IMAGE_DIRS})

add_executable(OPE2023 main.cpp
        Commons/Vector2.cpp
        Commons/Vector2.hpp
        Commons/Math.hpp
        Components/Component.cpp
        Components/Component.hpp
        GameObjects/GameObject.cpp
        GameObjects/GameObject.hpp
        Game.cpp
        Game.hpp
        Scenes/TitleScene.cpp
        Scenes/TitleScene.hpp
        Scenes/Scene.cpp
        Scenes/Scene.hpp
        Components/SpriteComponent.cpp
        Components/SpriteComponent.hpp
        GameObjects/TextObject.cpp
        GameObjects/TextObject.hpp
)

target_link_libraries(OPE2023 ${SDL2_LIBRARY})
target_link_libraries(OPE2023 ${SDL2_TTF_LIBRARY})
target_link_libraries(OPE2023 ${SDL2_IMAGE_LIBRARY})
