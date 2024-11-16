#pragma once

#include "ComponentArray.h"

namespace ECS {

    class ComponentManager {
    public:
        template<typename T>
        void RegisterComponent();

        template<typename T>
        ComponentType GetComponentType();

        template<typename T>
        void AddComponent(Entity entity, T component);

        template<typename T>
        void RemoveComponent(Entity entity);

        template<typename T>
        T& GetComponent(Entity entity);

        template<typename T>
        bool HasComponent(Entity entity);

        void EntityDestroyed(Entity entity);

    private:
        std::unordered_map<const char*, ComponentType> componentTypes{};
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays{};
        ComponentType nextComponentType{};

        template<typename T>
        std::shared_ptr<ComponentArray<T>> GetComponentArray();
    };

}


//�e���v���[�g�֐��̎���
namespace ECS {

    template<typename T>
    void ComponentManager::RegisterComponent() {
        const char* typeName = typeid(T).name();

        assert(componentTypes.find(typeName) == componentTypes.end() && "�R���|�[�l���g�^�C�v�͊��ɓo�^����Ă��܂��B");

        componentTypes[typeName] = nextComponentType;
        componentArrays[typeName] = std::make_shared<ComponentArray<T>>();

        ++nextComponentType;
    }

    template<typename T>
    ComponentType ComponentManager::GetComponentType() {
        const char* typeName = typeid(T).name();

        assert(componentTypes.find(typeName) != componentTypes.end() && "�R���|�[�l���g�^�C�v���o�^����Ă��܂���B");

        return componentTypes[typeName];
    }

    template<typename T>
    void ComponentManager::AddComponent(Entity entity, T component) {
        GetComponentArray<T>()->InsertData(entity, component);
    }

    template<typename T>
    void ComponentManager::RemoveComponent(Entity entity) {
        GetComponentArray<T>()->RemoveData(entity);
    }

    template<typename T>
    T& ComponentManager::GetComponent(Entity entity) {
        return GetComponentArray<T>()->GetData(entity);
    }

    template<typename T>
    bool ComponentManager::HasComponent(Entity entity) {
        return GetComponentArray<T>()->HasData(entity);
    }

    template<typename T>
    std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray() {
        const char* typeName = typeid(T).name();

        assert(componentTypes.find(typeName) != componentTypes.end() && "�R���|�[�l���g�^�C�v���o�^����Ă��܂���B");

        return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
    }

    inline void ComponentManager::EntityDestroyed(Entity entity) {
        for (auto const& pair : componentArrays) {
            auto const& component = pair.second;

            component->EntityDestroyed(entity);
        }
    }

}