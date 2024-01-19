//
// Created by hw21a105 on 2024/01/03.
//

#include "Game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "GameObjects/GameObject.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/BoxColliderComponent.hpp"
#include "Scenes/TitleScene.hpp"

Game::Game()
        : mWindow(nullptr), mRenderer(nullptr), mTickCount(0), mIsRunning(true),
          mGameOver(false), mScene(nullptr), mNextScene(nullptr), mScore(0) {
}

bool Game::Initialize() {
    // SDL関連初期化
    if (!InitSDL()) {
        SDL_Log("%s", SDL_GetError());
        return false;
    }
    // ゲーム時間取得
    mTickCount = SDL_GetTicks();

    // シーン初期化
    InitScene();

    return true;
}

// SDL関連初期化
bool Game::InitSDL() {
    // 初期化に失敗したらfalseを返す
    bool success = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0;
    if (!success) return false;

    mWindow = SDL_CreateWindow("SnowShooting", 100, 100, ScreenWidth, ScreenHeight, 0);
    if (!mWindow) return false;

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer) return false;

    success = IMG_Init(IMG_INIT_PNG) != 0;
    if (!success) return false;

    success = TTF_Init() == 0;
    if (!success) return false;

    return true;
}

void Game::InitScene() {
}

void Game::RunLoop() {
    // 開始シーンを設定
    mScene = new TitleScene(this);
    mNextScene = mScene;
    StartScene();

    while (mIsRunning) {
        // シーン更新処理
        UpdateScene();
        // シーン開始処理
        if (mScene != mNextScene) {
            delete mScene;
            mScene = mNextScene;
            StartScene();
        }
    }
}

void Game::StartScene() {
    mScene->Start();
}

void Game::UpdateScene() {
    // 入力検知
    ProcessInput();

    // 最低16msは待機
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));
    // フレームの経過時間を取得(最大50ms)
    float deltaTime = (float) (SDL_GetTicks() - mTickCount) / 1000.0f;
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }
    mTickCount = SDL_GetTicks();

    // シーン更新処理
    mScene->UpdateScene(deltaTime);
    // 出力処理
    GenerateOutput();
}

void Game::ProcessInput() {
    // SDLイベント
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: // ウィンドウが閉じられた時
                mIsRunning = false;
                break;
        }
    }
    // キー入力イベント
    const Uint8 *state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }

    // 各シーンの入力検知
    mScene->ProcessInput(state);
}

void Game::GenerateOutput() {
    // 背景色をクリア
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255); // 紺色
    SDL_RenderClear(mRenderer);

    for (auto component: mScene->GetSprites()) {
        component->Draw(mRenderer);
    }

    if (mIsDebug) {
        for (auto gameObject: mScene->GetGameObjects()) {
            gameObject->DebugDraw(mRenderer);
        }
    }

    // バックバッファとスワップ(ダブルバッファ)
    SDL_RenderPresent(mRenderer);
}

void Game::Shutdown() {
    // インスタンスを破棄
    while (!mGameObjects.empty()) {
        delete mGameObjects.back();
    }
    for (const auto &i: mCachedTextures) {
        SDL_DestroyTexture(i.second);
    }
    mCachedTextures.clear();
    // SDL関連の変数を破棄
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
    IMG_Quit();
}

// ファイル名からテクスチャをロードする
SDL_Texture *Game::LoadTexture(const std::string &fileName) {
    SDL_Texture *tex = nullptr;
    auto iter = mCachedTextures.find(fileName);
    if (iter != mCachedTextures.end()) {
        // キャッシュ済なら変数から取得
        tex = iter->second;
    } else {
        // テクスチャをロードする
        SDL_Surface *surf = IMG_Load(fileName.c_str());
        if (!surf) {
            SDL_Log("Error load texture file %s", fileName.c_str());
            return nullptr;
        }
        tex = SDL_CreateTextureFromSurface(mRenderer, surf);
        SDL_FreeSurface(surf);
        if (!tex) {
            SDL_Log("Error convert surface to texture %s", fileName.c_str());
            return nullptr;
        }
        // 変数にキャッシュする
        mCachedTextures.emplace(fileName.c_str(), tex);
    }
    return tex;
}