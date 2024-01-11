//
// Created by hw21a105 on 2024/01/03.
//

#include "Game.hpp"
#include <SDL2/SDL.h>
#include "GameObjects/GameObject.hpp"
#include "Components/SpriteComponent.hpp"
#include "Commons/Vector2.hpp"
#include "Scenes/TitleScene.hpp"

Game::Game()
        : mWindow(nullptr), mRenderer(nullptr), mTickCount(0), mIsRunning(true), mUpdatingGameObject(false),
          mGameOver(false), mScene(nullptr), mNextScene(nullptr) {
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

    return true;
}

void Game::InitScene() {
    // 背景の作成
    auto *bg = new GameObject(this);
    bg->SetPosition(Vector2(ScreenWidth / 2, ScreenHeight / 2));
    auto *bgSprite = new SpriteComponent(bg, 20);

    // https://opengameart.org/content/tower-defense-snow-background
    bgSprite->SetTexture(LoadTexture("snow_template1.jpg"));
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
        if (mScene->GetSceneName() != mNextScene->GetSceneName()) {
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

    // アクタ更新処理
    mUpdatingGameObject = true;
    for (auto gameObject: mGameObjects) {
        gameObject->Update(deltaTime);
    }
    mUpdatingGameObject = false;

    // 待機中のアクタを追加
    for (auto pending: mPendingGameObjects) {
        mGameObjects.emplace_back(pending);
    }
    mPendingGameObjects.clear();

    // 各シーンの更新処理
    mScene->Update(deltaTime);

    // 死亡したアクタを破棄
    std::vector<GameObject *> deadGameObjects;
    for (auto gameObject: mGameObjects) {
        if (gameObject->GetState() == GameObject::EDead) {
            deadGameObjects.emplace_back(gameObject);
        }
    }
    for (auto gameObject: deadGameObjects) {
        delete gameObject;
    }

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
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }

    // 各シーンの入力検知
    mScene->ProcessInput(state);
}

void Game::GenerateOutput() {
    // 背景色をクリア
    SDL_SetRenderDrawColor(mRenderer, 19, 56, 111, 255); // 紺色
    SDL_RenderClear(mRenderer);

    // スプライトを描画
    for (auto sprite: mSprites) {
        sprite->Draw(mRenderer);
    }

    // バックバッファとスワップ(ダブルバッファ)
    SDL_RenderPresent(mRenderer);
}

void Game::Shutdown() {
    // インスタンスを破棄
    while (!mGameObjects.empty()) {
        delete mGameObjects.back();
    }
    for (auto i: mCachedTextures) {
        SDL_DestroyTexture(i.second);
    }
    mCachedTextures.clear();
    // SDL関連の変数を破棄
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
    IMG_Quit();
}


// GameObject追加処理
void Game::AddGameObject(GameObject *gameObject) {
    // GameObject更新中ならPendingに格納
    mUpdatingGameObject
    ? mPendingGameObjects.emplace_back(gameObject)
    : mGameObjects.emplace_back(gameObject);
}

// GameObject削除処理
void Game::RemoveGameObject(GameObject *gameObject) {
    auto iter = std::find(mPendingGameObjects.begin(), mPendingGameObjects.end(), gameObject);
    if (iter != mPendingGameObjects.end()) {
        mPendingGameObjects.erase(iter);
    }
    iter = std::find(mGameObjects.begin(), mGameObjects.end(), gameObject);
    if (iter != mGameObjects.end()) {
        mGameObjects.erase(iter);
    }
}

// 描画中のスプライト追加処理
void Game::AddSprite(SpriteComponent *sprite) {
    // 描画順にソートして追加
    int myDrawOrder = sprite->GetDrawOrder();
    auto iter = mSprites.begin();
    for (; iter != mSprites.end(); ++iter) {
        if (myDrawOrder < (*iter)->GetDrawOrder()) {
            break;
        }
    }
    mSprites.insert(iter, sprite);
}

// 描画中のスプライト削除処理
void Game::RemoveSprite(SpriteComponent *sprite) {
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
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