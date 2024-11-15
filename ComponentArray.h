#pragma once

#include "Entity.h"

namespace ECS {

	// コンポーネント配列のインターフェース
    class IComponentArray {
    public:
		virtual ~IComponentArray() = default;                   // デストラクタ
    };

    template<typename T>
    class ComponentArray : public IComponentArray {
    public:
		void InsertData(Entity entity, T component);            // データの挿入
		void RemoveData(Entity entity);						    // データの削除
		T& GetData(Entity entity);							    // データの取得
		bool HasData(Entity entity);							// データの有無

    private:
		std::array<T, MAX_ENTITIES> componentArray{};		    //コンポーネントの配列
		std::unordered_map<Entity, size_t> entityToIndexMap{};   //エンティティIDからインデックスへのマップ
		std::unordered_map<size_t, Entity> indexToEntityMap{};   //インデックスからエンティティIDへのマップ
		size_t size{ 0 };									   //コンポーネントのサイズ
    };

}