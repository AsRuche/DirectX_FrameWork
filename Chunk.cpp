#include "Chunk.h"
#include "ComponentInfo.h"

namespace ECS {

    Chunk::Chunk(const Archetype& archetype)
        : mArchetype(archetype) {
        // �A�[�L�^�C�v�̃R���|�[�l���g���ƂɃ��������m��
        for (auto typeID : mArchetype.GetComponentTypes()) {
            // �e�R���|�[�l���g�̃T�C�Y�͗\�ߌ��肳��Ă���Ɖ���
            size_t  componentSize = ComponentInfo::GetComponentSize(typeID);
            mComponentData[typeID].resize(componentSize * MAX_CHUNK_SIZE);
        }
    }

    void Chunk::AddEntity(Entity entity, const std::unordered_map<ComponentTypeID, void*>& components) {
        // �ő�T�C�Y�𒴂��Ă��Ȃ����m�F
        if (mEntities.size() >= MAX_CHUNK_SIZE) {
            // �G���[����
            return;
        }

        mEntities.push_back(entity);

        // �e�R���|�[�l���g�f�[�^���`�����N���ɃR�s�[
        size_t index = mEntities.size() - 1;
        for (auto& [typeID, dataPtr] : components) {
            size_t componentSize = ComponentInfo::GetComponentSize(typeID);
            void* destination = &mComponentData[typeID][componentSize * index];
            std::memcpy(destination, dataPtr, componentSize);
        }
    }

    void Chunk::RemoveEntity(Entity entity) {
        // �G���e�B�e�B���������č폜
        // �ȗ����̂��ߏڍׂ͏ȗ�
    }

    const std::vector<Entity>& Chunk::GetEntities() const {
        return mEntities;
    }

    void* Chunk::GetComponentData(ComponentTypeID typeID) {
        return mComponentData[typeID].data();
    }

    size_t Chunk::GetEntityCount() const {
        return mEntities.size();
    }

    const Archetype& Chunk::GetArchetype() const {
        return mArchetype;
    }

}