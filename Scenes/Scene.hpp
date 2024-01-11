//
// Created by hw21a105 on 2024/01/04.
//

#ifndef OPE2023_SCENE_HPP
#define OPE2023_SCENE_HPP

#include <SDL2/SDL_image.h>
#include <string>

class Scene {
public:
    explicit Scene(class Game* game);
    virtual ~Scene();
    virtual void Start();
    virtual void Update(float deltaTime);
    virtual void ProcessInput(const Uint8* state);
    virtual std::string GetSceneName();

private:
    class GameObject* mGameObject;
    class GameObject* mPendingGameObject;


protected:
    class Game* mGame;

};


#endif //OPE2023_SCENE_HPP
