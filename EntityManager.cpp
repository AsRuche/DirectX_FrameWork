#include "EntityManager.h"


// コンストラクタ：利用可能なエンティティIDを初期化
EntityManager::EntityManager() {
	// 利用可能なエンティティIDを初期化
	for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
		// エンティティIDを利用可能リストに追加
		mAvailableEntities.push(entity);
	}
}

// エンティティの生成
Entity EntityManager::CreateEntity() {
	// エンティティ数が最大を超えないことを確認
	assert(mLivingEntityCount < MAX_ENTITIES && "最大エンティティ数を超えました。");

	// 利用可能なIDから新しいエンティティIDを取得
	Entity id = mAvailableEntities.front(); // 先頭のエンティティIDを取得
	mAvailableEntities.pop();				// 先頭のエンティティIDを削除
	++mLivingEntityCount;                   // エンティティ数を増やす

	return id;
}

// エンティティの削除
void EntityManager::DestroyEntity(Entity entity) {
	// 有効なエンティティIDであることを確認
	assert(entity < MAX_ENTITIES && "無効なエンティティIDです。");

	// シグネチャをリセットし、IDを利用可能リストに戻す
	mSignatures[entity].reset();        // シグネチャをリセット
	mAvailableEntities.push(entity);    // 利用可能リストに戻す
	--mLivingEntityCount;               // エンティティ数を減らす
}

// エンティティのシグネチャ設定
void EntityManager::SetSignature(Entity entity, Signature signature) {
	// 有効なエンティティIDであることを確認
	assert(entity < MAX_ENTITIES && "無効なエンティティIDです。");

	// 指定されたシグネチャをエンティティに設定
	mSignatures[entity] = signature;
}

// エンティティのシグネチャ取得
Signature EntityManager::GetSignature(Entity entity) {
	// 有効なエンティティIDであることを確認
	assert(entity < MAX_ENTITIES && "無効なエンティティIDです。");

	// エンティティのシグネチャを返す
	return mSignatures[entity];
}
