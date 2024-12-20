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

        // ���N���X�� Update ���\�b�h���I�[�o�[���C�h
        void Update(float deltaTime) override;

        // �K�v�ɉ����� ArchetypeManager ���Z�b�g���郁�\�b�h��ǉ�
        void SetArchetypeManager(ArchetypeManager* manager);

    private:
        std::set<ComponentTypeID> mRequiredComponents;
        ArchetypeManager* mArchetypeManager; // ArchetypeManager �ւ̃|�C���^
    };

}