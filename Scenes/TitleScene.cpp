//
// Created by hw21a105 on 2024/01/04.
//

#include "TitleScene.hpp"
#include "Scene.hpp"
#include "../Game.hpp"
#include "../GameObjects/GameObject.hpp"
#include <SDL2/SDL_ttf.h>

TitleScene::TitleScene(class Game *game) : Scene(game) {}

TitleScene::~TitleScene() {}

void TitleScene::Start() {
    // クリアフラグを初期化
    mGame->SetGameOver(false);

    const auto *title = new GameObject(mGame);

    auto *font = TTF_OpenFont("Assets/Fonts/arial.ttf", 24);
    auto *text = TTF_RenderUTF8_Blended(font, "Press Space or Enter to start", {255, 255, 255});
//    SDL_BlitSurface(text, NULL, screen, &scr_rect);
}

void TitleScene::Update(float deltaTime) {
}

void TitleScene::ProcessInput(const Uint8 *state) {
    // スペースかエンター押下でゲームシーンに遷移
    if (state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_RETURN]) {

    }
}

std::string TitleScene::GetSceneName() {
    return "TEST";
}
