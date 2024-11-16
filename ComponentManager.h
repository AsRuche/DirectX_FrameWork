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
		std::unordered_map<const char*, ComponentType> componentTypes{}; //コンポーネントタイプ名（型情報から取得した文字列）から内部的なコンポーネントタイプIDへのマップを保持
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays{};//コンポーネントタイプ名から、それぞれのコンポーネント配列（ComponentArray）への共有ポインタを保持
		ComponentType nextComponentType{};//新しいコンポーネントタイプIDを割り当てるためのカウンタ

		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray();
	};

}


//テンプレート関数の実装
namespace ECS {


	//コンポーネントの登録を行う関数
	template<typename T>
	void ComponentManager::RegisterComponent() {
		const char* typeName = typeid(T).name();//コンポーネントの型名を取得

		//コンポーネントタイプが登録されていないことを確認
		assert(componentTypes.find(typeName) == componentTypes.end() && "コンポーネントタイプは既に登録されています。");

		componentTypes[typeName] = nextComponentType;//新しいコンポーネントタイプIDを登録
		componentArrays[typeName] = std::make_shared<ComponentArray<T>>();//componentArraysに新しいcomponentArray<T>のインスタンスを作成して登録

		++nextComponentType;//次のコンポーネントタイプIDを更新
	}

	//コンポーネントタイプの取得
	template<typename T>
	ComponentType ComponentManager::GetComponentType() {
		const char* typeName = typeid(T).name();//コンポーネントの型名を取得

		//コンポーネントタイプが登録されていることを確認
		assert(componentTypes.find(typeName) != componentTypes.end() && "コンポーネントタイプが登録されていません。");

		//コンポーネントタイプIDを返す
		return componentTypes[typeName];
	}

	//特定のエンティティに対してコンポーネントTを追加
	template<typename T>
	void ComponentManager::AddComponent(Entity entity, T component) {
		GetComponentArray<T>()->InsertData(entity, component);//取得した配列のInsertData(entity, component)を呼び出して、エンティティとコンポーネントを追加
	}

	//特定のエンティティからコンポーネントTを削除
	template<typename T>
	void ComponentManager::RemoveComponent(Entity entity) {//取得した配列のRemoveData(entity)を呼び出して、エンティティからコンポーネントを削除
		GetComponentArray<T>()->RemoveData(entity);//取得した配列のRemoveData(entity)を呼び出して、エンティティからコンポーネントを削除
	}

	//定のエンティティに紐づくコンポーネントTを取得
	template<typename T>
	T& ComponentManager::GetComponent(Entity entity) {
		return GetComponentArray<T>()->GetData(entity); //GetComponentArray<T>()でコンポーネント配列を取得。配列のGetData(entity)を呼び出して、コンポーネントを取得
	}

	//特定のエンティティがコンポーネントTを持っているかどうかを確認
	template<typename T>
	bool ComponentManager::HasComponent(Entity entity) {
		return GetComponentArray<T>()->HasData(entity);//取得した配列のHasData(entity)を呼び出して、エンティティがコンポーネントを持っているかどうかを確認
	}

	//内部で使用される、特定のコンポーネントタイプTに対応するコンポーネント配列を取得
	template<typename T>
	std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray() {
		const char* typeName = typeid(T).name();//コンポーネントの型名を取得

		assert(componentTypes.find(typeName) != componentTypes.end() && "コンポーネントタイプが登録されていません。");//コンポーネントタイプが登録されていることを確認

		return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]); //componentArraysからコンポーネント配列を取得し、std::static_pointer_castでComponentArray<T>にキャストして返す
	}

	//エンティティが削除された際に、そのエンティティに関連するすべてのコンポーネントを削除
	inline void ComponentManager::EntityDestroyed(Entity entity) {
		for (auto const& pair : componentArrays) {//componentArraysに登録されているすべてのコンポーネント配列を順に処理
			auto const& component = pair.second;//コンポーネント配列を取得

			component->EntityDestroyed(entity); //各配列に対してEntityDestroyed(entity)を呼び出し、エンティティに関連するデータを削除
		}
	}

}