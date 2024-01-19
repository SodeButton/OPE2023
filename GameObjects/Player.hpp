//
// Created by hw21a105 on 2024/01/11.
//

#ifndef OPE2023_PLAYER_HPP
#define OPE2023_PLAYER_HPP

#include "GameObject.hpp"
#include <SDL2/SDL.h>

class Player : public GameObject {
public:
    explicit Player(class Scene *scene);

    ~Player() override;

    void UpdateGameObject(float deltaTime) override;

    void OnCollisionEnter(BoxColliderComponent *other) override;

    void ProcessInput(const Uint8 *state);

private:
    float mShotTimer;
    float mMoveSpeed;

    Vector2 mMoveDirection;
    Vector2 mBulletDirection;

    class SpriteComponent *mSprite;

    std::vector<class Bullet *> mBullets;

};

#endif //OPE2023_PLAYER_HPP
