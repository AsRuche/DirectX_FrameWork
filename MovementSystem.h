#pragma once

#include "System.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "ComponentType.h"
#include "ArchetypeManager.h"

namespace ECS {

    class MovementSystem : public System {
    public:
        MovementSystem();

        // 基底クラスの Update メソッドをオーバーライド
        void Update(float deltaTime) override;

        // 必要に応じて ArchetypeManager をセットするメソッドを追加
        void SetArchetypeManager(ArchetypeManager* manager);

    private:
        std::set<ComponentTypeID> mRequiredComponents;
        ArchetypeManager* mArchetypeManager; // ArchetypeManager へのポインタ
    };

}