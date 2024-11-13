#pragma once



// エンティティのIDを表す型定義
using Entity = uint32_t;

// 最大エンティティ数の定義
const Entity MAX_ENTITIES = 50000;

//コンポーネントの最大数を指定
const uint32_t MAX_COMPONENTS = 32;

// シグネチャの定義（ビットセットでコンポーネントの有無を管理）
using Signature = std::bitset<MAX_COMPONENTS>;//ビットセットでコンポーネントの有無を管理（ビットが立っているとコンポーネントが存在する）

class EntityManager {
public:
    // コンストラクタ：利用可能なエンティティIDを初期化
    EntityManager();

    // エンティティの生成
    Entity CreateEntity();

	// エンティティの削除（引数はエンティティID）
    void DestroyEntity(Entity entity);

	// エンティティのシグネチャ設定（引数はエンティティID ,シグネチャ）
    void SetSignature(Entity entity, Signature signature);

	// エンティティのシグネチャ取得（引数はエンティティID）
    Signature GetSignature(Entity entity);

private:
    // 利用可能なエンティティIDを管理するキュー
    std::queue<Entity> mAvailableEntities{};

    // エンティティごとのシグネチャを管理する配列
    std::array<Signature, MAX_ENTITIES> mSignatures{};

    // 現在のエンティティ数
    uint32_t mLivingEntityCount{};
};