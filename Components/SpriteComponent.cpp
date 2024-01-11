//
// Created by hw21a105 on 2024/01/10.
//

#include "SpriteComponent.hpp"
#include "../Game.hpp"
#include "../GameObjects/GameObject.hpp"
#include "../Commons/Math.hpp"

SpriteComponent::SpriteComponent(GameObject *gameObject, int drawOrder)
        : Component(gameObject),
          mTexture(nullptr),
          mDrawOrder(drawOrder),
          mTexWidth(0),
          mTexHeight(0) {
    mGameObject->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
    mGameObject->GetGame()->RemoveSprite(this);
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
                         SDL_FLIP_NONE);
    }
}

// テクスチャ設定処理
void SpriteComponent::SetTexture(SDL_Texture *texture) {
    mTexture = texture;
    // テクスチャから幅を設定
    SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
