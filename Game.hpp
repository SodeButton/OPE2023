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

    void AddGameObject(class GameObject *gameObject);

    void RemoveGameObject(class GameObject *gameObject);

    void AddSprite(class SpriteComponent *sprite);

    void RemoveSprite(class SpriteComponent *sprite);

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
    bool mUpdatingGameObject;    // ゲームオブジェクト更新中か否か？
    bool mGameOver;         // ゲームをクリアしたか否か？

    class Scene *mScene;

    class Scene *mNextScene;

public:
    // getter, setter
    Scene *GetNextScene() const { return mNextScene; }

    void SetNextScene(class Scene *scene) { mNextScene = scene; }

    Scene *GetScene() const { return mScene; }

    void SetScene(class Scene *scene) { mScene = scene; }

    std::vector<class GameObject *> GetGameObjects() { return mGameObjects; }

    void SetGameOver(const bool isGameOver) { mGameOver = isGameOver; }

    bool GetGameOver() const { return mGameOver; }

};


#endif //OPE2023_GAME_HPP
