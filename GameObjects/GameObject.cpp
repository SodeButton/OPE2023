//
// Created by hw21a105 on 2023/12/20.
//

#include "GameObject.hpp"
#include "../Game.hpp"
#include "../Components/Component.hpp"
#include "../Scenes/Scene.hpp"
#include "../Commons/Utility.hpp"
#include <SDL2/SDL_ttf.h>

GameObject::GameObject(Scene *scene)
        : mScene(scene),
          mState(EActive),
          mPosition(Vector2::Zero),
          mScale(Vector2::One),
          mRotation(0.0f),
          mName("Default"),
          mTag("Default"),
          mFont(nullptr) {
    mScene->AddGameObject(this);
}

GameObject::~GameObject() {
    mScene->RemoveGameObject(this);
    while (!mComponents.empty()) {
        delete mComponents.back();
    }
    TTF_CloseFont(mFont);
}

void GameObject::Update(float deltaTime) {
    if (mState == EActive) {
        UpdateComponents(deltaTime);
        UpdateGameObject(deltaTime);
    }
}

void GameObject::UpdateComponents(float deltaTime) {
    for (auto component: mComponents) {
        component->Update(deltaTime);
    }
}

void GameObject::UpdateGameObject(float deltaTime) {}

void GameObject::AddComponent(Component *component) {
    int order = component->GetUpdateOrder();
    auto iter = mComponents.begin();
    for (; iter != mComponents.end(); ++iter) {
        if (order < (*iter)->GetUpdateOrder()) {
            break;
        }
    }
    mComponents.insert(iter, component);
}

void GameObject::RemoveComponent(Component *component) {
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if (iter != mComponents.end()) {
        mComponents.erase(iter);
    }
}

void GameObject::OnCollisionEnter(BoxColliderComponent *other) {}

void GameObject::OnCollisionStay(BoxColliderComponent *other) {}

void GameObject::DebugDraw(SDL_Renderer *renderer) {
    for (auto component: mComponents) {
        component->DebugDraw(renderer);
    }

    auto posText =
            "(" + Utility::FloatToString(mPosition.x) + ", " +
            Utility::FloatToString(mPosition.y) + ")";
    if (mFont == nullptr) {
        mFont = TTF_OpenFont("/Library/Fonts/Arial Unicode.ttf", 16);
    }

    auto surface = TTF_RenderUTF8_Blended(mFont, posText.c_str(), {0, 0, 0, 255});
    auto texture = SDL_CreateTextureFromSurface(renderer, surface);
    int texWidth;  // テクスチャ横幅
    int texHeight; // テクスチャ縦幅
    SDL_QueryTexture(texture, nullptr, nullptr, &texWidth, &texHeight);

    //Textureを描写する
    if (texture) {
        SDL_Rect r;
        // 大きさ、位置（左上座標）を設定
        r.w = static_cast<int>((float) texWidth);
        r.h = static_cast<int>((float) texHeight);
        r.x = static_cast<int>(mPosition.x - (float) r.w / 2.0);
        r.y = static_cast<int>(mPosition.y - (float) r.h / 2.0 - 30);
        // 描画
        SDL_RenderCopyEx(renderer,
                         texture,
                         nullptr,
                         &r,
                         0,
                         nullptr,
                         SDL_FLIP_NONE);
    }
}