#include "EntityManager.h"
#include <cassert>

namespace ECS {

    EntityManager::EntityManager() : livingEntityCount(0) {
        // 利用可能なエンティティIDをキューに格納
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
            availableEntities.push(entity);
        }
    }

    Entity EntityManager::CreateEntity() {
        assert(livingEntityCount < MAX_ENTITIES && "最大エンティティ数を超えました。");

        Entity id = availableEntities.front();
        availableEntities.pop();
        ++livingEntityCount;

        return id;
    }

    void EntityManager::DestroyEntity(Entity entity) {
        assert(entity < MAX_ENTITIES && "無効なエンティティIDです。");

        // シグネチャをリセット
        signatures[entity].reset();

        availableEntities.push(entity);
        --livingEntityCount;
    }

    void EntityManager::SetSignature(Entity entity, Signature signature) {
        assert(entity < MAX_ENTITIES && "無効なエンティティIDです。");

        signatures[entity] = signature;
    }

    Signature EntityManager::GetSignature(Entity entity) const {
        assert(entity < MAX_ENTITIES && "無効なエンティティIDです。");

        return signatures[entity];
    }

}