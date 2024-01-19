//
// Created by hw21a105 on 2024/01/16.
//

#ifndef OPE2023_ENEMY_HPP
#define OPE2023_ENEMY_HPP

#include "GameObject.hpp"

class Enemy : public GameObject {
public:
    explicit Enemy(class Scene *scene);

    ~Enemy() override;

    void UpdateGameObject(float deltaTime) override;

    void OnCollisionEnter(BoxColliderComponent *other) override;

private:
    class SpriteComponent *mSprite;

    class Vector2 mVelocity;

    float mMoveSpeed;

    class Player *mPlayer;

public:

    [[maybe_unused]] [[nodiscard]] const Vector2 &GetVelocity() const { return mVelocity; }

    [[maybe_unused]] void SetVelocity(const Vector2 &velocity) { mVelocity = velocity; }

    void SetPlayer(class Player *player) { mPlayer = player; }
};


#endif //OPE2023_ENEMY_HPP