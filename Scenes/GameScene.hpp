//
// Created by hw21a105 on 2024/01/11.
//

#ifndef OPE2023_GAMESCENE_HPP
#define OPE2023_GAMESCENE_HPP

#include "Scene.hpp"

class GameScene : public Scene {
public:
    explicit GameScene(class Game *game);

    ~GameScene() override = default;

    void Start() override;

    void Update(float deltaTime) override;

    void ProcessInput(const Uint8 *state) override;

    std::string GetSceneName() override;

private:
    class Player *mPlayer;

    class TextObject *mScoreText;

    std::vector<class Enemy *> mEnemies;

    float mEnemySpawnTime = 4.0f;
    float mEnemySpawnTimer = 0.0f;

    bool mSetGameOverMessage = false;

};


#endif //OPE2023_GAMESCENE_HPP
