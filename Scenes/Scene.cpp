//
// Created by hw21a105 on 2024/01/04.
//

#include "Scene.hpp"
#include "../Game.hpp"

Scene::Scene(class Game* game)
        :mGame(game){
}

Scene::~Scene() = default;

void Scene::Start() {}

void Scene::Update(float deltaTime) {}

void Scene::ProcessInput(const Uint8* state) {}

std::string Scene::GetSceneName() {
    return "";
}
