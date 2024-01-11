//
// Created by hw21a105 on 2024/01/10.
//

#ifndef OPE2023_SPRITECOMPONENT_HPP
#define OPE2023_SPRITECOMPONENT_HPP

#include <SDL2/SDL.h>
#include "Component.hpp"

class SpriteComponent : public Component {

public:
    SpriteComponent(GameObject *gameObject, int drawOrder = 100);

    ~SpriteComponent();

    virtual void Draw(SDL_Renderer *renderer);

    virtual void SetTexture(SDL_Texture *texture);

protected:
    SDL_Texture *mTexture;
    int mDrawOrder; // 描画順
    int mTexWidth;  // テクスチャ横幅
    int mTexHeight; // テクスチャ縦幅

public:
    // Getter, Setter
    int GetDrawOrder() const { return mDrawOrder; }

    int GetTexWidth() const { return mTexWidth; }

    int GetTexHeight() const { return mTexHeight; }
};


#endif //OPE2023_SPRITECOMPONENT_HPP
