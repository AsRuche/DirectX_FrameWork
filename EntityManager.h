#pragma once

#include "Entity.h"
#include "Component.h"

namespace ECS {

	// エンティティマネージャ（エンティティの生成、削除、シグネチャの設定）
    class EntityManager {
    public:
		EntityManager();                                        // コンストラクタ

		Entity CreateEntity();								    // エンティティの生成
		void DestroyEntity(Entity entity);					    // エンティティの削除

		void SetSignature(Entity entity, Signature signature);  //エンティティのシグネチャ設定
        Signature GetSignature(Entity entity) const;

    private:
		std::queue<Entity> availableEntities{};                 // 利用可能なエンティティIDのキュー
		std::array<Signature, MAX_ENTITIES> signatures{};		// エンティティのシグネチャ
		uint32_t livingEntityCount{};							// 現在のエンティティ数
    };

}