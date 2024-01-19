//
// Created by hw21a105 on 2024/01/04.
//

#include "Scene.hpp"
#include "../Game.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../GameObjects/GameObject.hpp"

Scene::Scene(class Game *game)
        : mGame(game), mUpdatingGameObject(false) {
}

Scene::~Scene() {
    for (auto gameObject: mGameObjects) {
        gameObject->SetState(GameObject::EDead);
    }
};

void Scene::Start() {}

void Scene::Update(float deltaTime) {}

void Scene::ProcessInput(const Uint8 *state) {}

std::string Scene::GetSceneName() {
    return "";
}

void Scene::UpdateScene(float deltaTime) {
    // アクタ更新処理
    mUpdatingGameObject = true;
    for (auto gameObject: mGameObjects) {
        gameObject->Update(deltaTime);
    }
    mUpdatingGameObject = false;

    // 待機中のアクタを追加
    for (auto pending: mPendingGameObjects) {
        mGameObjects.emplace_back(pending);
    }
    mPendingGameObjects.clear();

    for (auto boxCollider: mBoxColliders) {
        // 衝突判定処理
        if (boxCollider->GetGameObject()->GetState() != GameObject::EActive) {
            continue;
        }
        for (auto other: mBoxColliders) {
            if (other->GetGameObject()->GetState() != GameObject::EActive) {
                continue;
            }
            if (boxCollider == other) {
                continue;
            }
            boxCollider->OnCollisionEnter(other);
        }
    }

    this->Update(deltaTime);

    // 死亡したアクタを破棄
    std::vector<GameObject *> deadGameObjects;
    for (auto gameObject: mGameObjects) {
        if (gameObject->GetState() == GameObject::EDead) {
            deadGameObjects.emplace_back(gameObject);
        }
    }
    for (auto gameObject: deadGameObjects) {
        delete gameObject;
    }
}

// GameObject追加処理
void Scene::AddGameObject(GameObject *gameObject) {
    // GameObject更新中ならPendingに格納
    mUpdatingGameObject
    ? mPendingGameObjects.emplace_back(gameObject)
    : mGameObjects.emplace_back(gameObject);
}

// GameObject削除処理
void Scene::RemoveGameObject(GameObject *gameObject) {
    auto iter = std::find(mPendingGameObjects.begin(), mPendingGameObjects.end(), gameObject);
    if (iter != mPendingGameObjects.end()) {
        mPendingGameObjects.erase(iter);
    }
    iter = std::find(mGameObjects.begin(), mGameObjects.end(), gameObject);
    if (iter != mGameObjects.end()) {
        mGameObjects.erase(iter);
    }
}

// 描画中のスプライト追加処理
void Scene::AddSprite(SpriteComponent *sprite) {
    // 描画順にソートして追加
    int myDrawOrder = sprite->GetDrawOrder();
    auto iter = mSprites.begin();
    for (; iter != mSprites.end(); ++iter) {
        if (myDrawOrder < (*iter)->GetDrawOrder()) {
            break;
        }
    }
    mSprites.insert(iter, sprite);
}

// 描画中のスプライト削除処理
void Scene::RemoveSprite(SpriteComponent *sprite) {
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}

// 衝突判定中のBoxCollider追加処理
void Scene::AddBoxCollider(BoxColliderComponent *boxCollider) {
    mBoxColliders.emplace_back(boxCollider);
}

// 衝突判定中のBoxCollider削除処理
void Scene::RemoveBoxCollider(BoxColliderComponent *boxCollider) {
    auto iter = std::find(mBoxColliders.begin(), mBoxColliders.end(), boxCollider);
    mBoxColliders.erase(iter);
}

