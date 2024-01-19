//
// Created by hw21a105 on 2024/01/11.
//

#ifndef OPE2023_TEXTCOMPONENT_HPP
#define OPE2023_TEXTCOMPONENT_HPP

#include "SpriteComponent.hpp"
#include <SDL2/SDL_ttf.h>
#include <string>

class TextComponent : public SpriteComponent {
public:
    TextComponent(class GameObject *gameObject, int drawOrder = 100);

    ~TextComponent();

    void Draw(SDL_Renderer *renderer) override;

protected:
    SDL_Surface *mSurface;
    TTF_Font *mFont;
    int mFontSize;
    std::string mText;
    std::string mFontPath;
    SDL_Color mColor;

public:
    void SetText(const std::string &text) { mText = text; }

    void SetColor(const SDL_Color &color) { mColor = color; }

    void SetFontSize(int size) {
        TTF_CloseFont(mFont);
        mFontSize = size;
        mFont = TTF_OpenFont(mFontPath.c_str(), mFontSize);
    }

    void SetFontPath(const std::string &fontPath) {
        TTF_CloseFont(mFont);
        mFontPath = fontPath;
        mFont = TTF_OpenFont(mFontPath.c_str(), mFontSize);
    };
};


#endif //OPE2023_TEXTCOMPONENT_HPP
