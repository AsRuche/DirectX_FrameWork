#include "EntityManager.h"
#include <cassert>

namespace ECS {

    EntityManager::EntityManager() : livingEntityCount(0) {
        // ���p�\�ȃG���e�B�e�BID���L���[�Ɋi�[
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
            availableEntities.push(entity);
        }
    }

    Entity EntityManager::CreateEntity() {
        assert(livingEntityCount < MAX_ENTITIES && "�ő�G���e�B�e�B���𒴂��܂����B");

        Entity id = availableEntities.front();
        availableEntities.pop();
        ++livingEntityCount;

        return id;
    }

    void EntityManager::DestroyEntity(Entity entity) {
        assert(entity < MAX_ENTITIES && "�����ȃG���e�B�e�BID�ł��B");

        // �V�O�l�`�������Z�b�g
        signatures[entity].reset();

        availableEntities.push(entity);
        --livingEntityCount;
    }

    void EntityManager::SetSignature(Entity entity, Signature signature) {
        assert(entity < MAX_ENTITIES && "�����ȃG���e�B�e�BID�ł��B");

        signatures[entity] = signature;
    }

    Signature EntityManager::GetSignature(Entity entity) const {
        assert(entity < MAX_ENTITIES && "�����ȃG���e�B�e�BID�ł��B");

        return signatures[entity];
    }

}