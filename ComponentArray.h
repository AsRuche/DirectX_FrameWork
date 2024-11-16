#pragma once

#include "Entity.h"

namespace ECS {


	//IComponentArrayは、コンポーネント配列の基底クラス
	// すべてのコンポーネント配列は、このクラスを継承する必要がある
	class IComponentArray {
	public:
		virtual ~IComponentArray() = default;				//デストラクタ
		virtual void EntityDestroyed(Entity entity) = 0;	//エンティティが破棄されたときに呼び出される
	};


	//忘備録的メモ
	//このComponentArray<T>クラスは、ECSにおいて、特定のコンポーネント型Tに対応するすべてのエンティティのコンポーネントを管理するためのもの

	//このテンプレートクラスは、特定のコンポーネントの配列を保持し、エンティティとそのコンポーネントのインデックスを追跡
	template<typename T>
	class ComponentArray : public IComponentArray {
	public:

		//新しいエンティティにコンポーネントを追加
		void InsertData(Entity entity, T component) {

			//エンティティが既に存在するかどうかを確認
			assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && "コンポーネントは既に追加されています。");

			size_t newIndex = size;					 //newIndexに現在のsizeを設定
			entityToIndexMap[entity] = newIndex;	 //エンティティとそのインデックスを登録
			indexToEntityMap[newIndex] = entity;	 //インデックスとそのエンティティを登録
			componentArray[newIndex] = component;	 //componentArrayのnewIndex位置にコンポーネントを格納
			++size;									 //コンポーネントの数を増やす
		}

		//指定したエンティティからコンポーネントを削除
		//この関数は、エンティティを削除する場合に最後のコンポーネントを移動するため、順序を維持する
		void RemoveData(Entity entity) {

			//エンティティがentityToIndexMapに存在することを確認
			assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "コンポーネントが存在しません。");

			size_t indexOfRemovedEntity = entityToIndexMap[entity];                     //削除するエンティティのインデックス
			size_t indexOfLastElement = size - 1;                                       //配列の最後の要素のインデックス
			componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];  //配列の最後のコンポーネントを、削除対象の位置に上書きする。配列の中間の要素を削除する際のギャップを防ぐ

			Entity lastEntity = indexToEntityMap[indexOfLastElement];                   //lastEntityを取得し、そのエンティティのインデックスを更新
			entityToIndexMap[lastEntity] = indexOfRemovedEntity;						//エンティティのインデックスを更新、移動したコンポーネントの新しい位置を反映
			indexToEntityMap[indexOfRemovedEntity] = lastEntity;						//インデックスのエンティティを更新、移動したコンポーネントの新しい位置を反映

			entityToIndexMap.erase(entity);												//削除対象のエンティティのエントリをentityToIndexMapとindexToEntityMapから削除
			indexToEntityMap.erase(indexOfLastElement);									//同上

			--size;																		//コンポーネント数を更新
		}

		//指定したエンティティに関連付けられたコンポーネントへの参照を取得
		T& GetData(Entity entity) {
			//エンティティが存在することを確認
			assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "コンポーネントが存在しません。");

			//エンティティに関連付けられたコンポーネントへの参照を返す
			return componentArray[entityToIndexMap[entity]];//componentArray[entityToIndexMap[entity]]はエンティティに関連付けられたコンポーネントへの参照
		}

		//エンティティがコンポーネントを持っているかどうかを確認
		bool HasData(Entity entity) {
			return entityToIndexMap.find(entity) != entityToIndexMap.end();//EntityToIndexMapにエンティティが存在するかをチェックし、その結果を返す
		}


		//エンティティが破棄されたときに、関連するコンポーネントを削除
		void EntityDestroyed(Entity entity) override {
			if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {//エンティティが存在するかどうかを確認
				RemoveData(entity);//エンティティが存在する場合、関連するコンポーネントを削除
			}
		}

	private:
		std::array<T, MAX_ENTITIES> componentArray{};                                    //固定サイズの配列で、各コンポーネントのデータを格納
		std::unordered_map<Entity, size_t> entityToIndexMap{};						     //エンティティから配列のインデックスへのマッピングを保持
		std::unordered_map<size_t, Entity> indexToEntityMap{};						     //配列のインデックスからエンティティへのマッピングを保持
		size_t size{};  													             //コンポーネントの数
	};

}