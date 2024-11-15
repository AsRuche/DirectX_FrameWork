#pragma once

#include "System.h"
#include "Coordinator.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"

class MovementSystem : public ECS::System {
public:
    void Update(ECS::Coordinator& coordinator, float deltaTime) {
        for (auto const& entity : entities) {
            auto& position = coordinator.GetComponent<PositionComponent>(entity);
            auto& velocity = coordinator.GetComponent<VelocityComponent>(entity);

            position.x += velocity.x * deltaTime;
            position.y += velocity.y * deltaTime;
        }
    }
};