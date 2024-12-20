#pragma once

#include "Entity.h"

namespace ECS {

    // �G���e�B�e�B���Ǘ�����N���X
    class EntityManager {
    public:
        EntityManager();

        // �G���e�B�e�B�̐���
        Entity CreateEntity();

        // �G���e�B�e�B�̔j��
        void DestroyEntity(Entity entity);

    private:
        std::queue<Entity> mAvailableEntities; // �ė��p�\�ȃG���e�B�e�BID
        Entity mNextEntityID; // ���Ɋ��蓖�Ă�G���e�B�e�BID
    };

}