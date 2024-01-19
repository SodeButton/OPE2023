//
// Created by hw21a105 on 2024/01/11.
//

#include "GameScene.hpp"
#include "Scene.hpp"
#include "../Game.hpp"
#include "../GameObjects/GameObject.hpp"
#include "../GameObjects/TextObject.hpp"
#include "../GameObjects/Player.hpp"
#include "../GameObjects/Enemy.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Commons/Math.hpp"

GameScene::GameScene(class Game *game) : Scene(game), mPlayer(nullptr), mScoreText(nullptr) {}

void GameScene::Start() {

    // 背景の作成
    auto *bg = new GameObject(this);
    bg->SetPosition(Vector2(1280 / 2, 720 / 2));
    auto *bgSprite = new SpriteComponent(bg, 20);
    // https://opengameart.org/content/tower-defense-snow-background
    bgSprite->SetTexture(mGame->LoadTexture("snow_template1.jpg"));

    // スコア
    mScoreText = new TextObject(this, 110);
    mScoreText->SetPosition(Vector2(1280 / 2, 720 / 10));
    mScoreText->SetText("Score: 0");
    mScoreText->SetColor(SDL_Color{0, 0, 0, 255});
    mScoreText->SetFontSize(32);

    mPlayer = new Player(this);

    mEnemySpawnTimer = mEnemySpawnTime;
//
//    auto *enemy = new Enemy(this);
//    int edge = Math::GetRand(0, 1);
//    float x = 1280.0f / 2.0f;
//    float y = 720.0f / 2.0f;
//    enemy->SetPosition(Vector2(x, y));
//    enemy->SetPlayer(mPlayer);
//    mEnemies.emplace_back(enemy);
}

void GameScene::Update(float deltaTime) {
    // 敵の生成
    mEnemySpawnTimer -= deltaTime;
    if (mEnemySpawnTimer <= 0.0f) {
        auto *enemy = new Enemy(this);
        int edge = Math::GetRand(0, 1);
        float x = edge == 0 ? (float) Math::GetRand(0, 1) * 1280.0f : Math::GetRand(0.0f, 1280.0f);
        float y = edge == 0 ? Math::GetRand(0.0f, 720.0f) : (float) Math::GetRand(0, 1) * 720.0f;
        enemy->SetPosition(Vector2(x, y));
        enemy->SetPlayer(mPlayer);
        mEnemies.emplace_back(enemy);

        mEnemySpawnTimer = mEnemySpawnTime;
        mEnemySpawnTime *= 0.9f;
    }
    std::string score = std::to_string(mGame->GetScore());
    score = std::string(7 - score.length(), '0') + score;
    mScoreText->SetText("Score: " + score);

    if (GetGame()->GetGameOver()) {
        if (!mSetGameOverMessage) {
            auto *gameOverText = new TextObject(this, 110);
            gameOverText->SetPosition(Vector2(1280 / 2, 720 / 4));
            gameOverText->SetText("Game Over");
            gameOverText->SetColor(SDL_Color{255, 0, 0, 255});
            gameOverText->SetFontSize(128);
            mSetGameOverMessage = true;

            auto *restartText = new TextObject(this, 110);
            restartText->SetPosition(Vector2(1280 / 2.0f, 720 / 1.3f));
            restartText->SetText("Press R to Restart");
            restartText->SetColor(SDL_Color{0, 0, 0, 255});
            restartText->SetFontSize(32);
        }
    }
}

void GameScene::ProcessInput(const Uint8 *state) {
    mPlayer->ProcessInput(state);

    if (mSetGameOverMessage) {
        if (state[SDL_SCANCODE_R]) {
            mGame->SetScore(0);
            mGame->SetGameOver(false);
            mGame->SetNextScene(new GameScene(mGame));
        }
    }
}

std::string GameScene::GetSceneName() {
    return "GameScene";
}