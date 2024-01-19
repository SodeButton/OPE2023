//
// Created by hw21a105 on 2024/01/16.
//

#ifndef OPE2023_BULLET_HPP
#define OPE2023_BULLET_HPP

#include "GameObject.hpp"

class Bullet : public GameObject {
public:
    explicit Bullet(class Scene *scene);

    ~Bullet() override;

    void UpdateGameObject(float deltaTime) override;

private:
    class SpriteComponent *mSprite;

    class Vector2 mVelocity;

public:
    [[maybe_unused]] [[nodiscard]] const Vector2 &GetVelocity() const { return mVelocity; }

    [[maybe_unused]] void SetVelocity(const Vector2 &velocity) { mVelocity = velocity; }
};


#endif //OPE2023_BULLET_HPP
