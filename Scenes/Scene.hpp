//
// Created by hw21a105 on 2024/01/04.
//

#ifndef OPE2023_SCENE_HPP
#define OPE2023_SCENE_HPP

#include <SDL2/SDL_image.h>
#include <string>

class Scene {
public:
    explicit Scene(class Game *game);

    virtual ~Scene();

    virtual void Start();

    virtual void Update(float deltaTime);

    virtual void ProcessInput(const Uint8 *state);

    virtual std::string GetSceneName();

    void UpdateScene(float deltaTime);

    void AddGameObject(class GameObject *gameObject);

    void RemoveGameObject(class GameObject *gameObject);

    void AddSprite(class SpriteComponent *sprite);

    void RemoveSprite(class SpriteComponent *sprite);

    void AddBoxCollider(class BoxColliderComponent *boxCollider);

    void RemoveBoxCollider(class BoxColliderComponent *boxCollider);

private:
    bool mUpdatingGameObject;    // ゲームオブジェクト更新中か否か？

    std::vector<class GameObject *> mGameObjects;
    std::vector<class GameObject *> mPendingGameObjects;
    std::vector<class SpriteComponent *> mSprites;
    std::vector<class BoxColliderComponent *> mBoxColliders;

protected:
    class Game *mGame;

public:
    [[nodiscard]] class Game *GetGame() const { return mGame; }

    [[nodiscard]] const std::vector<class GameObject *> &GetGameObjects() const { return mGameObjects; }

    [[nodiscard]] const std::vector<class SpriteComponent *> &GetSprites() const { return mSprites; }

    [[nodiscard]] const std::vector<class BoxColliderComponent *> &GetBoxColliders() const { return mBoxColliders; }
};


#endif //OPE2023_SCENE_HPP
