//
// Created by hw21a105 on 2024/01/16.
//

#include "Enemy.hpp"
#include "../Scenes/Scene.hpp"
#include "../Game.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../GameObjects/Player.hpp"

Enemy::Enemy(class Scene *scene) : GameObject(scene), mMoveSpeed(100.0f), mPlayer(nullptr) {
    mSprite = new SpriteComponent(this, 100);
    mSprite->SetTexture(GetScene()->GetGame()->LoadTexture("enemy01.png"));
    auto *boxCollider = new BoxColliderComponent(this);
    boxCollider->SetOffset(Vector2(0.0f, 8.0f));
    boxCollider->SetSize(Vector2(24.0f, 45.0f));
    SetTag("Enemy");
}

Enemy::~Enemy() = default;

void Enemy::UpdateGameObject(float deltaTime) {
    if (mPlayer != nullptr) {
        mVelocity = mPlayer->GetPosition() - GetPosition();
        mVelocity = mVelocity.Normalize();
        if (mVelocity.x < 0.0f) {
            mSprite->SetFlip(SDL_FLIP_NONE);
        } else {
            mSprite->SetFlip(SDL_FLIP_HORIZONTAL);
        }
    }
    SetPosition(GetPosition() + mVelocity * mMoveSpeed * deltaTime);
}

void Enemy::OnCollisionEnter(BoxColliderComponent *other) {
    if (other->GetGameObject()->GetTag() == "Bullet") {
        SetState(EDead);
        other->GetGameObject()->SetState(EDead);
        GetScene()->GetGame()->AddScore(100);
    }
}