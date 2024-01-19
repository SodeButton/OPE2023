//
// Created by hw21a105 on 2024/01/11.
//

#include "Player.hpp"
#include "../Game.hpp"
#include "../Scenes/Scene.hpp"
#include "../GameObjects/Bullet.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"

Player::Player(class Scene *scene) : GameObject(scene), mBulletDirection(Vector2::Zero), mShotTimer(0.0f),
                                     mMoveSpeed(200.0f) {
    // プレイヤーの作成
    SetPosition(Vector2(1280 / 2, 720 / 2));
    mSprite = new SpriteComponent(this, 100);
    mSprite->SetTexture(scene->GetGame()->LoadTexture("snowman.png"));
    auto *boxCollider = new BoxColliderComponent(this);
    boxCollider->SetOffset(Vector2(0.0f, 8.0f));
    boxCollider->SetSize(Vector2(36.0f, 45.0f));
    SetTag("Player");
}

Player::~Player() {
    // 弾の削除
    for (auto bullet: mBullets) {
        bullet->SetState(EDead);
    }
    mBullets.clear();

}

void Player::UpdateGameObject(float deltaTime) {
    // プレイヤーの移動処理
    if (mMoveDirection.Length() > 0.0f) {
        SetPosition(GetPosition() + mMoveDirection.Normalize() * mMoveSpeed * deltaTime);
    }
    mShotTimer -= deltaTime;
}

void Player::OnCollisionEnter(BoxColliderComponent *other) {
    // 衝突処理
    if (other->GetGameObject()->GetTag() == "Enemy") {
        GetScene()->GetGame()->SetGameOver(true);
        other->GetGameObject()->SetState(EDead);
        SetState(EPaused);
    }
}

void Player::ProcessInput(const Uint8 *state) {
    if (GetState() != EActive) {
        return;
    }
    // プレイヤーの移動処理
    mMoveDirection = Vector2::Zero;
    if (state[SDL_SCANCODE_W]) {
        mMoveDirection.y = -1.0f;
    }
    if (state[SDL_SCANCODE_S]) {
        mMoveDirection.y = 1.0f;
    }
    if (state[SDL_SCANCODE_A]) {
        mMoveDirection.x = -1.0f;
        mSprite->SetFlip(SDL_FLIP_HORIZONTAL);
    }
    if (state[SDL_SCANCODE_D]) {
        mMoveDirection.x = 1.0f;
        mSprite->SetFlip(SDL_FLIP_NONE);
    }

    if (mMoveDirection.Length() == 0.0f) {
        if (mBulletDirection.Length() == 0.0f) {
            mBulletDirection = Vector2(0.0f, -1.0f);
        }
    } else {
        mBulletDirection = mMoveDirection;
    }

    if (state[SDL_SCANCODE_SPACE] && mShotTimer <= 0.0f) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        Vector2 mousePos = Vector2(mouseX, mouseY);
        Vector2 velocity = mousePos - GetPosition();
        // 弾の作成1
        auto *bullet = new Bullet(GetScene());
        bullet->SetPosition(GetPosition());
        bullet->SetVelocity(velocity.Normalize());
        mShotTimer = 1.0f;
    }
}
