//
// Created by hw21a105 on 2024/01/16.
//

#include "Bullet.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Scenes/Scene.hpp"
#include "../Game.hpp"

Bullet::Bullet(class Scene *scene) : GameObject(scene) {
    mSprite = new SpriteComponent(this, 100);
    mSprite->SetTexture(GetScene()->GetGame()->LoadTexture("snowball.png"));
    SetScale(Vector2(0.2f, 0.2f));
    auto *boxCollider = new BoxColliderComponent(this);
    boxCollider->SetOffset(Vector2(0.0f, 0.0f));
    boxCollider->SetSize(Vector2(24.0f, 24.0f));
    SetTag("Bullet");
}

Bullet::~Bullet() = default;

void Bullet::UpdateGameObject(float deltaTime) {
    SetPosition(GetPosition() + mVelocity * deltaTime * 300.0f);

    // 画面外に出たら削除
    if (GetPosition().x < -100.0f || GetPosition().x > 1380.0f || GetPosition().y < -100.0f ||
        GetPosition().y > 820.0f) {
        SetState(EDead);
    }
}