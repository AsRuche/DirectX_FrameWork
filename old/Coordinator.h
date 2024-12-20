#pragma once

#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

namespace ECS {

    class Coordinator {
    public:
        void Init();

        // �G���e�B�e�B�֘A
        Entity CreateEntity();
        void DestroyEntity(Entity entity);

        // �R���|�[�l���g�֘A
        template<typename T>
        void RegisterComponent();

		// �R���|�[�l���g�̒ǉ��A�폜�A�擾�A�L���̊m�F
        template<typename T>
        void AddComponent(Entity entity, T component);

		// �R���|�[�l���g�̍폜
        template<typename T>
        void RemoveComponent(Entity entity);

		// �R���|�[�l���g�̎擾
        template<typename T>
        T& GetComponent(Entity entity);

		// �R���|�[�l���g�̗L��
        template<typename T>
        bool HasComponent(Entity entity);

        // �V�X�e���֘A
        template<typename T>
        std::shared_ptr<T> RegisterSystem();

		// �V�O�l�`���̐ݒ�
        template<typename T>
        void SetSystemSignature(Signature signature);

    private:
        std::unique_ptr<EntityManager> entityManager{};
        std::unique_ptr<ComponentManager> componentManager{};
        std::unique_ptr<SystemManager> systemManager{};
    };

}