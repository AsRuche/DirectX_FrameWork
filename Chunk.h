#pragma once

#include "Entity.h"
#include "Archetype.h"
#include "ComponentType.h"

namespace ECS {

    // �`�����N���̃G���e�B�e�B���̍ő�l�i����j
    const size_t MAX_CHUNK_SIZE = 1024;

    // �`�����N��\���N���X
    class Chunk {
    public:
        // �R���X�g���N�^�F�A�[�L�^�C�v�ŏ�����
        Chunk(const Archetype& archetype);

        // �G���e�B�e�B���`�����N�ɒǉ�
        void AddEntity(Entity entity, const std::unordered_map<ComponentTypeID, void*>& components);

        // �G���e�B�e�B���`�����N����폜
        void RemoveEntity(Entity entity);

        // �G���e�B�e�B�̃��X�g���擾
        const std::vector<Entity>& GetEntities() const;

        // �R���|�[�l���g�f�[�^�ւ̃|�C���^���擾
        void* GetComponentData(ComponentTypeID typeID);

        // ���݂̃G���e�B�e�B�����擾
        size_t GetEntityCount() const;

        // �A�[�L�^�C�v���擾
        const Archetype& GetArchetype() const;

    private:
        Archetype mArchetype; // ���̃`�����N�̃A�[�L�^�C�v
        std::vector<Entity> mEntities; // �G���e�B�e�B�̃��X�g
        std::unordered_map<ComponentTypeID, std::vector<uint8_t>> mComponentData; // �R���|�[�l���g�f�[�^
    };

}