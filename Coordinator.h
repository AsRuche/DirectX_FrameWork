#pragma once

#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

namespace ECS {

    class Coordinator {
    public:
        void Init();

        // エンティティ関連
        Entity CreateEntity();
        void DestroyEntity(Entity entity);

        // コンポーネント関連
        template<typename T>
        void RegisterComponent();

		// コンポーネントの追加、削除、取得、有無の確認
        template<typename T>
        void AddComponent(Entity entity, T component);

		// コンポーネントの削除
        template<typename T>
        void RemoveComponent(Entity entity);

		// コンポーネントの取得
        template<typename T>
        T& GetComponent(Entity entity);

		// コンポーネントの有無
        template<typename T>
        bool HasComponent(Entity entity);

        // システム関連
        template<typename T>
        std::shared_ptr<T> RegisterSystem();

		// シグネチャの設定
        template<typename T>
        void SetSystemSignature(Signature signature);

    private:
        std::unique_ptr<EntityManager> entityManager{};
        std::unique_ptr<ComponentManager> componentManager{};
        std::unique_ptr<SystemManager> systemManager{};
    };

}