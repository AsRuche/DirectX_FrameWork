#pragma once
#include "Archetype.h"
#include "Chunk.h"
#include "Entity.h"

namespace ECS {

    // �A�[�L�^�C�v�ƃ`�����N���Ǘ�����N���X
    class ArchetypeManager {
    public:
        // �G���e�B�e�B��ǉ��i�K�v�ɉ����ă`�����N���쐬�j
        void AddEntity(Entity entity, const std::set<ComponentTypeID>& componentTypes,
            const std::unordered_map<ComponentTypeID, void*>& components);

        // �G���e�B�e�B���폜
        void RemoveEntity(Entity entity);

        // �K�v�ȃR���|�[�l���g�����`�����N���擾
        std::vector<std::shared_ptr<Chunk>> GetChunks(const std::set<ComponentTypeID>& requiredComponents);

    private:
        // �A�[�L�^�C�v���Ƃ̃`�����N�̃}�b�v
        std::unordered_map<Archetype, std::vector<std::shared_ptr<Chunk>>> mArchetypeChunks;

        // �G���e�B�e�BID�Ə�������`�����N�̃}�b�v
        std::unordered_map<Entity, std::weak_ptr<Chunk>> mEntityChunkMap;
    };

}