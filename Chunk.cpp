#include "Chunk.h"
#include "ComponentInfo.h"

namespace ECS {

    Chunk::Chunk(const Archetype& archetype)
        : mArchetype(archetype) {
        // アーキタイプのコンポーネントごとにメモリを確保
        for (auto typeID : mArchetype.GetComponentTypes()) {
            // 各コンポーネントのサイズは予め決定されていると仮定
            size_t  componentSize = ComponentInfo::GetComponentSize(typeID);
            mComponentData[typeID].resize(componentSize * MAX_CHUNK_SIZE);
        }
    }

    void Chunk::AddEntity(Entity entity, const std::unordered_map<ComponentTypeID, void*>& components) {
        // 最大サイズを超えていないか確認
        if (mEntities.size() >= MAX_CHUNK_SIZE) {
            // エラー処理
            return;
        }

        mEntities.push_back(entity);

        // 各コンポーネントデータをチャンク内にコピー
        size_t index = mEntities.size() - 1;
        for (auto& [typeID, dataPtr] : components) {
            size_t componentSize = ComponentInfo::GetComponentSize(typeID);
            void* destination = &mComponentData[typeID][componentSize * index];
            std::memcpy(destination, dataPtr, componentSize);
        }
    }

    void Chunk::RemoveEntity(Entity entity) {
        // エンティティを検索して削除
        // 簡略化のため詳細は省略
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