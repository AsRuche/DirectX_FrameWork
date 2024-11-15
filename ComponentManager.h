#pragma once

#include "ComponentArray.h"
#include "Component.h"

namespace ECS {

    class ComponentManager {
    public:
        template<typename T>
		void RegisterComponent();           //コンポーネントの登録

        template<typename T>
		ComponentType GetComponentType()    ;//コンポーネントタイプの取得

        template<typename T>
		void AddComponent(Entity entity, T component);  //コンポーネントの追加

        template<typename T>
		void RemoveComponent(Entity entity);    //コンポーネントの削除

        template<typename T>
		T& GetComponent(Entity entity);		    //コンポーネントの取得

        template<typename T>
		bool HasComponent(Entity entity);	    //コンポーネントの有無

    private:
		std::unordered_map<const char*, ComponentType> componentTypes{}; //コンポーネントタイプのマップ
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays{}; //コンポーネント配列のマップ
		ComponentType nextComponentType{}; //次のコンポーネントタイプ

        template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray(); //コンポーネント配列の取得
    };

}
