#include "MovementSystem.h"

namespace ECS {

    MovementSystem::MovementSystem() {
        // 必要なコンポーネントタイプを登録
        mRequiredComponents.insert(GetComponentTypeID<PositionComponent>());
        mRequiredComponents.insert(GetComponentTypeID<VelocityComponent>());
    }

    void MovementSystem::Update(ArchetypeManager& archetypeManager, float deltaTime) {
        // 必要なコンポーネントを持つチャンクを取得
        auto chunks = archetypeManager.GetChunks(mRequiredComponents);

        for (auto& chunk : chunks) {
            size_t entityCount = chunk->GetEntityCount();

            // コンポーネントデータへのポインタを取得
            PositionComponent* positions = static_cast<PositionComponent*>(chunk->GetComponentData(GetComponentTypeID<PositionComponent>()));
            VelocityComponent* velocities = static_cast<VelocityComponent*>(chunk->GetComponentData(GetComponentTypeID<VelocityComponent>()));

            // エンティティごとに処理
            for (size_t i = 0; i < entityCount; ++i) {
                positions[i].x += velocities[i].vx * deltaTime;
                positions[i].y += velocities[i].vy * deltaTime;
                positions[i].z += velocities[i].vz * deltaTime;
            }
        }
    }

}