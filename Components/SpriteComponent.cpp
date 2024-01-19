//
// Created by hw21a105 on 2024/01/10.
//

#include <math.h>
#include "SpriteComponent.hpp"
#include "../Game.hpp"
#include "../GameObjects/GameObject.hpp"
#include "../Commons/Math.hpp"
#include "../Scenes/Scene.hpp"

SpriteComponent::SpriteComponent(GameObject *gameObject, int drawOrder)
        : Component(gameObject),
          mFlip(SDL_FLIP_NONE),
          mTexture(nullptr),
          mDrawOrder(drawOrder),
          mTexWidth(0),
          mTexHeight(0) {
    mGameObject->GetScene()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
    mGameObject->GetScene()->RemoveSprite(this);
    Component::~Component();
}

void SpriteComponent::Draw(SDL_Renderer *renderer) {
    if (mTexture) {
        SDL_Rect r;
        // 大きさ、位置（左上座標）を設定
        r.w = static_cast<int>((float) mTexWidth * mGameObject->GetScale().x);
        r.h = static_cast<int>((float) mTexHeight * mGameObject->GetScale().y);
        r.x = static_cast<int>(mGameObject->GetPosition().x - (float) r.w / 2.0);
        r.y = static_cast<int>(mGameObject->GetPosition().y - (float) r.h / 2.0);
        // 描画
        SDL_RenderCopyEx(renderer,
                         mTexture,
                         nullptr,
                         &r,
                         -mGameObject->GetRotation() * Math::Rad2Deg(),
                         nullptr,
                         mFlip);
    }
}

void SpriteComponent::DebugDraw(SDL_Renderer *renderer) {
    SDL_Rect r;
    r.w = static_cast<int>((float) mTexWidth * mGameObject->GetScale().x);
    r.h = static_cast<int>((float) mTexHeight * mGameObject->GetScale().y);
    r.x = static_cast<int>(mGameObject->GetPosition().x - (float) r.w / 2.0);
    r.y = static_cast<int>(mGameObject->GetPosition().y - (float) r.h / 2.0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &r);

    float rad = mGameObject->GetRotation() * Math::Deg2Rad();
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLineF(renderer,
                        mGameObject->GetPosition().x,
                        mGameObject->GetPosition().y,
                        mGameObject->GetPosition().x + cos(rad) * 50.0f,
                        mGameObject->GetPosition().y + sin(rad) * 50.0f);

    rad = (mGameObject->GetRotation() + 90) * Math::Deg2Rad();
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawLineF(renderer,
                        mGameObject->GetPosition().x,
                        mGameObject->GetPosition().y,
                        mGameObject->GetPosition().x + cos(rad) * 50.0f,
                        mGameObject->GetPosition().y + sin(rad) * 50.0f);


}

// テクスチャ設定処理
void SpriteComponent::SetTexture(SDL_Texture *texture) {
    mTexture = texture;
    // テクスチャから幅を設定
    SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
