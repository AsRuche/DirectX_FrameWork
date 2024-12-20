#include "EntityManager.h"
#include <cassert>

#include "EntityManager.h"

namespace ECS {

    EntityManager::EntityManager() : mNextEntityID(0) {}

    Entity EntityManager::CreateEntity() {
        Entity id;
        if (!mAvailableEntities.empty()) {
            id = mAvailableEntities.front();
            mAvailableEntities.pop();
        }
        else {
            id = mNextEntityID++;
        }
        return id;
    }

    void EntityManager::DestroyEntity(Entity entity) {
        // �ė��p�\�ȃG���e�B�e�BID�Ƃ��ĕۑ�
        mAvailableEntities.push(entity);
    }

}