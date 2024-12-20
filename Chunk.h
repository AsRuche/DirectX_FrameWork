#pragma once

#include "Entity.h"
#include "Archetype.h"
#include "ComponentType.h"

namespace ECS {

    // チャンク内のエンティティ数の最大値（仮定）
    const size_t MAX_CHUNK_SIZE = 1024;

    // チャンクを表すクラス
    class Chunk {
    public:
        // コンストラクタ：アーキタイプで初期化
        Chunk(const Archetype& archetype);

        // エンティティをチャンクに追加
        void AddEntity(Entity entity, const std::unordered_map<ComponentTypeID, void*>& components);

        // エンティティをチャンクから削除
        void RemoveEntity(Entity entity);

        // エンティティのリストを取得
        const std::vector<Entity>& GetEntities() const;

        // コンポーネントデータへのポインタを取得
        void* GetComponentData(ComponentTypeID typeID);

        // 現在のエンティティ数を取得
        size_t GetEntityCount() const;

        // アーキタイプを取得
        const Archetype& GetArchetype() const;

    private:
        Archetype mArchetype; // このチャンクのアーキタイプ
        std::vector<Entity> mEntities; // エンティティのリスト
        std::unordered_map<ComponentTypeID, std::vector<uint8_t>> mComponentData; // コンポーネントデータ
    };

}