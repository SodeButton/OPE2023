//
// Created by hw21a105 on 2024/01/03.
//

#ifndef OPE2023_GAME_HPP
#define OPE2023_GAME_HPP

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class Game {
public:
    Game();

    bool Initialize();

    void RunLoop();

    void Shutdown();

    SDL_Texture *LoadTexture(const std::string &fileName);

    constexpr static const int ScreenWidth = 1280;
    constexpr static const int ScreenHeight = 720;

private:
    bool InitSDL();

    void InitScene();

    void StartScene();     // シーン開始処理
    void UpdateScene();    // シーン更新処理
    void ProcessInput();   // 入力検知
    void GenerateOutput(); // 出力処理

    std::vector<class GameObject *> mGameObjects;
    std::vector<class GameObject *> mPendingGameObjects;
    std::vector<class SpriteComponent *> mSprites;

    std::unordered_map<std::string, SDL_Texture *> mCachedTextures; // キャッシュしたテクスチャリスト

    SDL_Window *mWindow;     // SDLウィンドウ
    SDL_Renderer *mRenderer; // SDLレンダラー
    Uint32 mTickCount;      // ゲーム時間
    bool mIsRunning;         // 実行中か否か？
    bool mGameOver;         // ゲームをクリアしたか否か？

    class Scene *mScene;

    class Scene *mNextScene;

    int mScore;

    bool mIsDebug = false;

public:
    // getter, setter
    [[nodiscard]] Scene *GetNextScene() const { return mNextScene; }

    void SetNextScene(class Scene *scene) { mNextScene = scene; }

    [[nodiscard]] SDL_Window *GetWindow() const { return mWindow; }

    [[nodiscard]] SDL_Renderer *GetRenderer() const { return mRenderer; }

    [[nodiscard]] Scene *GetScene() const { return mScene; }

    void SetScene(class Scene *scene) { mScene = scene; }

    std::vector<class GameObject *> GetGameObjects() { return mGameObjects; }

    void SetGameOver(const bool isGameOver) { mGameOver = isGameOver; }

    [[nodiscard]] bool GetGameOver() const { return mGameOver; }

    void AddScore(const int score) { mScore += score; }

    void SetScore(const int score) { mScore = score; }

    [[nodiscard]] int GetScore() const { return mScore; }
};


#endif //OPE2023_GAME_HPP
