#pragma once

#include "ComponentArray.h"
#include "Component.h"

namespace ECS {

    class ComponentManager {
    public:
        template<typename T>
		void RegisterComponent();           //�R���|�[�l���g�̓o�^

        template<typename T>
		ComponentType GetComponentType()    ;//�R���|�[�l���g�^�C�v�̎擾

        template<typename T>
		void AddComponent(Entity entity, T component);  //�R���|�[�l���g�̒ǉ�

        template<typename T>
		void RemoveComponent(Entity entity);    //�R���|�[�l���g�̍폜

        template<typename T>
		T& GetComponent(Entity entity);		    //�R���|�[�l���g�̎擾

        template<typename T>
		bool HasComponent(Entity entity);	    //�R���|�[�l���g�̗L��

    private:
		std::unordered_map<const char*, ComponentType> componentTypes{}; //�R���|�[�l���g�^�C�v�̃}�b�v
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays{}; //�R���|�[�l���g�z��̃}�b�v
		ComponentType nextComponentType{}; //���̃R���|�[�l���g�^�C�v

        template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray(); //�R���|�[�l���g�z��̎擾
    };

}
