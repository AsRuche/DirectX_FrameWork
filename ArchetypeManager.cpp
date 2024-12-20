#include "ArchetypeManager.h"

namespace ECS {

    void ArchetypeManager::AddEntity(Entity entity, const std::set<ComponentTypeID>& componentTypes,
        const std::unordered_map<ComponentTypeID, void*>& components) {
        Archetype archetype(componentTypes);

        // アーキタイプに対応するチャンクを取得または作成
        auto& chunks = mArchetypeChunks[archetype];
        std::shared_ptr<Chunk> targetChunk;

        for (auto& chunk : chunks) {
            if (chunk->GetEntityCount() < MAX_CHUNK_SIZE) {
                targetChunk = chunk;
                break;
            }
        }

        if (!targetChunk) {
            // 新しいチャンクを作成
            targetChunk = std::make_shared<Chunk>(archetype);
            chunks.push_back(targetChunk);
        }

        // エンティティをチャンクに追加
        targetChunk->AddEntity(entity, components);

        // エンティティとチャンクの関連付け
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

            // 必要なコンポーネントを全て含むか確認
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