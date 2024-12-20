#pragma once

#include "Entity.h"

namespace ECS {

    // エンティティを管理するクラス
    class EntityManager {
    public:
        EntityManager();

        // エンティティの生成
        Entity CreateEntity();

        // エンティティの破棄
        void DestroyEntity(Entity entity);

    private:
        std::queue<Entity> mAvailableEntities; // 再利用可能なエンティティID
        Entity mNextEntityID; // 次に割り当てるエンティティID
    };

}