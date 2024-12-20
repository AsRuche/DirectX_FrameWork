#include "ArchetypeManager.h"

namespace ECS {

    void ArchetypeManager::AddEntity(Entity entity, const std::set<ComponentTypeID>& componentTypes,
        const std::unordered_map<ComponentTypeID, void*>& components) {
        Archetype archetype(componentTypes);

        // �A�[�L�^�C�v�ɑΉ�����`�����N���擾�܂��͍쐬
        auto& chunks = mArchetypeChunks[archetype];
        std::shared_ptr<Chunk> targetChunk;

        for (auto& chunk : chunks) {
            if (chunk->GetEntityCount() < MAX_CHUNK_SIZE) {
                targetChunk = chunk;
                break;
            }
        }

        if (!targetChunk) {
            // �V�����`�����N���쐬
            targetChunk = std::make_shared<Chunk>(archetype);
            chunks.push_back(targetChunk);
        }

        // �G���e�B�e�B���`�����N�ɒǉ�
        targetChunk->AddEntity(entity, components);

        // �G���e�B�e�B�ƃ`�����N�̊֘A�t��
        mEntityChunkMap[entity] = targetChunk;
    }

    void ArchetypeManager::RemoveEntity(Entity entity) {
        auto it = mEntityChunkMap.find(entity);
        if (it != mEntityChunkMap.end()) {
            auto chunk = it->second.lock();
            if (chunk) {
                chunk->RemoveEntity(entity);
            }
            mEntityChunkMap.erase(it);
        }
    }

    std::vector<std::shared_ptr<Chunk>> ArchetypeManager::GetChunks(const std::set<ComponentTypeID>& requiredComponents) {
        std::vector<std::shared_ptr<Chunk>> result;

        for (auto& [archetype, chunks] : mArchetypeChunks) {
            auto& componentTypes = archetype.GetComponentTypes();

            // �K�v�ȃR���|�[�l���g��S�Ċ܂ނ��m�F
            bool containsAll = true;
            for (auto& typeID : requiredComponents) {
                if (componentTypes.find(typeID) == componentTypes.end()) {
                    containsAll = false;
                    break;
                }
            }

            if (containsAll) {
                result.insert(result.end(), chunks.begin(), chunks.end());
            }
        }

        return result;
    }

}