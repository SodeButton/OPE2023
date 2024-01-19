//
// Created by hw21a105 on 2024/01/16.
//

#include "BoxColliderComponent.hpp"
#include "../GameObjects/GameObject.hpp"
#include "../Scenes/Scene.hpp"
#include "../Game.hpp"

BoxColliderComponent::BoxColliderComponent(GameObject *gameObject) : Component(gameObject) {
    mGameObject->GetScene()->AddBoxCollider(this);
}

BoxColliderComponent::~BoxColliderComponent() {
    mGameObject->GetScene()->RemoveBoxCollider(this);
    Component::~Component();
}

bool BoxColliderComponent::OnCollisionEnter(BoxColliderComponent *other) {
    Vector2 pos = GetGameObject()->GetPosition();
    Vector2 otherPos = other->GetGameObject()->GetPosition();

    bool onHit = false;

    //衝突判定
    if (pos.x - mSize.x / 2.0f < otherPos.x + other->GetSize().x / 2.0f &&
        pos.x + mSize.x / 2.0f > otherPos.x - other->GetSize().x / 2.0f &&
        pos.y - mSize.y / 2.0f < otherPos.y + other->GetSize().y / 2.0f &&
        pos.y + mSize.y / 2.0f > otherPos.y - other->GetSize().y / 2.0f) {
        onHit = true;
    }

    if (onHit) {
        GetGameObject()->OnCollisionEnter(other);
    }
    return onHit;
}

void BoxColliderComponent::OnCollisionStay(BoxColliderComponent *other) {

}

void BoxColliderComponent::Update(float deltaTime) {}

void BoxColliderComponent::DebugDraw(SDL_Renderer *renderer) {
    SDL_Rect r;
    r.x = (int) (GetGameObject()->GetPosition().x + mOffset.x - mSize.x / 2.0f);
    r.y = (int) (GetGameObject()->GetPosition().y + mOffset.y - mSize.y / 2.0f);
    r.w = (int) mSize.x;
    r.h = (int) mSize.y;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &r);
}