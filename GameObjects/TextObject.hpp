//
// Created by hw21a105 on 2024/01/11.
//

#ifndef OPE2023_TEXTOBJECT_HPP
#define OPE2023_TEXTOBJECT_HPP

#include "GameObject.hpp"
#include "../Components/TextComponent.hpp"

class TextObject : public GameObject {
public:
    TextObject(class Scene *scene, int drawOrder = 100);

    ~TextObject() override;

    class TextComponent *mTextComponent;

    void SetText(const std::string &text) { mTextComponent->SetText(text); }

    void SetColor(const SDL_Color &color) { mTextComponent->SetColor(color); }

    void SetFontSize(int size) { mTextComponent->SetFontSize(size); }

    void SetFontPath(const std::string &fontPath) { mTextComponent->SetFontPath(fontPath); };

};


#endif //OPE2023_TEXTOBJECT_HPP
