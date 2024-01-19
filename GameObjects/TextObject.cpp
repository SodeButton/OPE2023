//
// Created by hw21a105 on 2024/01/11.
//

#include "TextObject.hpp"

TextObject::TextObject(Scene *scene, int drawOrder)
        : GameObject(scene) {
    // TextComponentを追加
    mTextComponent = new TextComponent(this, drawOrder);
    AddComponent(mTextComponent);
}

TextObject::~TextObject() {
    delete mTextComponent;
};