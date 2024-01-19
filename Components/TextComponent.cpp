//
// Created by hw21a105 on 2024/01/11.
//

#include "TextComponent.hpp"
#include "../GameObjects/GameObject.hpp"
#include "../Commons/Math.hpp"

TextComponent::TextComponent(GameObject *gameObject, int drawOrder)
        : SpriteComponent(gameObject, drawOrder), mSurface(nullptr), mFontSize(24), mFont(nullptr),
          mFontPath("/Library/Fonts/Arial Unicode.ttf"), mColor({255, 255, 255, 255}) {
    mFont = TTF_OpenFont(mFontPath.c_str(), mFontSize);
}

TextComponent::~TextComponent() {
    if (mTexture) {
        SDL_DestroyTexture(mTexture);
    }
    if (mFont) {
        TTF_CloseFont(mFont);
    }
    if (mSurface) {
        SDL_FreeSurface(mSurface);
    }
}

void TextComponent::Draw(SDL_Renderer *renderer) {

    mSurface = TTF_RenderUTF8_Blended(mFont, mText.c_str(), mColor);
    mTexture = SDL_CreateTextureFromSurface(renderer, mSurface);
    SDL_QueryTexture(mTexture, nullptr, nullptr, &mTexWidth, &mTexHeight);

    //Textureを描写する
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

