//
// Created by hw21a105 on 2024/01/16.
//

#ifndef OPE2023_BOXCOLLIDERCOMPONENT_HPP
#define OPE2023_BOXCOLLIDERCOMPONENT_HPP

#include "Component.hpp"
#include <SDL2/SDL.h>
#include "../Commons/Vector2.hpp"

class BoxColliderComponent : public Component {
public:
    explicit BoxColliderComponent(GameObject *gameObject);

    ~BoxColliderComponent() override;

    bool OnCollisionEnter(BoxColliderComponent *other);

    void OnCollisionStay(BoxColliderComponent *other);

    void Update(float deltaTime) override;

    void DebugDraw(struct SDL_Renderer *renderer) override;

private:
    Vector2 mOffset;
    Vector2 mSize;
public:

    const Vector2 &GetOffset() const { return mOffset; }

    void SetOffset(const Vector2 &offset) { mOffset = offset; }

    const Vector2 &GetSize() const { return mSize; }

    void SetSize(const Vector2 &size) { mSize = size; }
};


#endif //OPE2023_BOXCOLLIDERCOMPONENT_HPP
