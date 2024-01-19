//
// Created by hw21a105 on 2024/01/04.
//

#ifndef OPE2023_TITLESCENE_HPP
#define OPE2023_TITLESCENE_HPP

#include "Scene.hpp"

class TitleScene : public Scene {
public:
    explicit TitleScene(class Game *game);

    ~TitleScene() override = default;

    void Start() override;

    void Update(float deltaTime) override;

    void ProcessInput(const Uint8 *state) override;

    std::string GetSceneName() override;

private:

};


#endif //OPE2023_TITLESCENE_HPP
