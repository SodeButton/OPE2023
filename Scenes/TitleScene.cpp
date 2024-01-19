//
// Created by hw21a105 on 2024/01/04.
//

#include "TitleScene.hpp"
#include "GameScene.hpp"
#include "Scene.hpp"
#include "../Game.hpp"
#include "../GameObjects/GameObject.hpp"
#include "../GameObjects/TextObject.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TextComponent.hpp"

TitleScene::TitleScene(class Game *game) : Scene(game) {}

void TitleScene::Start() {
    // クリアフラグを初期化
    mGame->SetGameOver(false);

    // 背景の作成
    auto *bg = new GameObject(this);
    bg->SetPosition(Vector2(1280 / 2, 720 / 2));
    auto *bgSprite = new SpriteComponent(bg, 20);

    // https://opengameart.org/content/tower-defense-snow-background
    bgSprite->SetTexture(mGame->LoadTexture("snow_template1.jpg"));

    auto *titleText = new TextObject(this);
    titleText->SetPosition(Vector2(1280 / 2, 720 / 3));
    titleText->SetText("SnowShooting");
    titleText->SetColor(SDL_Color{0, 0, 0, 255});
    titleText->SetFontSize(120);

    auto *authorText = new TextObject(this);
    authorText->SetPosition(Vector2(1280 / 1.25f, 720 / 1.05f));
    authorText->SetText("by HW21A105 Takuya HAYASHI");
    authorText->SetColor(SDL_Color{0, 0, 0, 255});
    authorText->SetFontSize(32);

    auto *startText = new TextObject(this);
    startText->SetPosition(Vector2(1280 / 2.0f, 720 / 1.5f));
    startText->SetText("Press Space or Enter to Start");
    startText->SetColor(SDL_Color{0, 0, 0, 255});
    startText->SetFontSize(30);

}

void TitleScene::Update(float deltaTime) {
}

void TitleScene::ProcessInput(const Uint8 *state) {
    // スペースかエンター押下でゲームシーンに遷移

    if (state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_RETURN]) {
        GetGame()->SetNextScene(new GameScene(mGame));
        printf("GameScene\n");
    }
}

std::string TitleScene::GetSceneName() {
    return "TEST";
}
