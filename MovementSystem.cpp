#include "MovementSystem.h"

namespace ECS {

    MovementSystem::MovementSystem() {
        // �K�v�ȃR���|�[�l���g�^�C�v��o�^
        mRequiredComponents.insert(GetComponentTypeID<PositionComponent>());
        mRequiredComponents.insert(GetComponentTypeID<VelocityComponent>());
    }

    void MovementSystem::Update(ArchetypeManager& archetypeManager, float deltaTime) {
        // �K�v�ȃR���|�[�l���g�����`�����N���擾
        auto chunks = archetypeManager.GetChunks(mRequiredComponents);

        for (auto& chunk : chunks) {
            size_t entityCount = chunk->GetEntityCount();

            // �R���|�[�l���g�f�[�^�ւ̃|�C���^���擾
            PositionComponent* positions = static_cast<PositionComponent*>(chunk->GetComponentData(GetComponentTypeID<PositionComponent>()));
            VelocityComponent* velocities = static_cast<VelocityComponent*>(chunk->GetComponentData(GetComponentTypeID<VelocityComponent>()));

            // �G���e�B�e�B���Ƃɏ���
            for (size_t i = 0; i < entityCount; ++i) {
                positions[i].x += velocities[i].vx * deltaTime;
                positions[i].y += velocities[i].vy * deltaTime;
                positions[i].z += velocities[i].vz * deltaTime;
            }
        }
    }

}