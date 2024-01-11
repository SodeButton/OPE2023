//
// Created by hw21a105 on 2024/01/04.
//

#ifndef OPE2023_TITLESCENE_HPP
#define OPE2023_TITLESCENE_HPP

#include "Scene.hpp"

class TitleScene : public Scene {
public:
    TitleScene(class Game* game);
    ~TitleScene();
    void Start() override;
    void Update(float deltaTime) override;
    void ProcessInput(const Uint8* state) override;
    std::string GetSceneName() override;

private:
    class GameObject* mStartMsg; // 開始メッセージ

};


#endif //OPE2023_TITLESCENE_HPP
