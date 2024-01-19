//
// Created by hw21a105 on 2023/12/20.
//

#ifndef OPE2023_COMPONENT_HPP
#define OPE2023_COMPONENT_HPP

class Component {
public:
    explicit Component(class GameObject *owner, int updateOrder = 100);

    virtual ~Component();

    virtual void Update(float deltaTime);

    virtual void DebugDraw(struct SDL_Renderer *renderer);

protected:
    class GameObject *mGameObject;

    int mUpdateOrder;

public:
    [[nodiscard]] int GetUpdateOrder() const { return mUpdateOrder; }

    [[nodiscard]] class GameObject *GetGameObject() const { return mGameObject; }
};


#endif //OPE2023_COMPONENT_HPP
