//
// Created by hw21a105 on 2024/01/10.
//

#ifndef OPE2023_SPRITECOMPONENT_HPP
#define OPE2023_SPRITECOMPONENT_HPP

#include <SDL2/SDL.h>
#include "Component.hpp"

class SpriteComponent : public Component {

public:
    explicit SpriteComponent(GameObject *gameObject, int drawOrder = 100);

    ~SpriteComponent() override;

    virtual void Draw(SDL_Renderer *renderer);

    virtual void SetTexture(SDL_Texture *texture);

    void DebugDraw(SDL_Renderer *renderer) override;

protected:
    SDL_Texture *mTexture;
    SDL_RendererFlip mFlip;
    int mDrawOrder; // 描画順
    int mTexWidth;  // テクスチャ横幅
    int mTexHeight; // テクスチャ縦幅

public:
    // Getter, Setter
    int GetDrawOrder() const { return mDrawOrder; }

    int GetTexWidth() const { return mTexWidth; }

    int GetTexHeight() const { return mTexHeight; }

    void SetFlip(SDL_RendererFlip flip) { mFlip = flip; }
};


#endif //OPE2023_SPRITECOMPONENT_HPP
