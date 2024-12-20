#pragma once
#include "Archetype.h"
#include "Chunk.h"
#include "Entity.h"

namespace ECS {

    // アーキタイプとチャンクを管理するクラス
    class ArchetypeManager {
    public:
        // エンティティを追加（必要に応じてチャンクを作成）
        void AddEntity(Entity entity, const std::set<ComponentTypeID>& componentTypes,
            const std::unordered_map<ComponentTypeID, void*>& components);

        // エンティティを削除
        void RemoveEntity(Entity entity);

        // 必要なコンポーネントを持つチャンクを取得
        std::vector<std::shared_ptr<Chunk>> GetChunks(const std::set<ComponentTypeID>& requiredComponents);

    private:
        // アーキタイプごとのチャンクのマップ
        std::unordered_map<Archetype, std::vector<std::shared_ptr<Chunk>>> mArchetypeChunks;

        // エンティティIDと所属するチャンクのマップ
        std::unordered_map<Entity, std::weak_ptr<Chunk>> mEntityChunkMap;
    };

}