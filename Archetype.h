#pragma once

#include "ComponentType.h"

namespace ECS {

    // アーキタイプを表すクラス
    class Archetype {
    public:
        // コンストラクタ：コンポーネントタイプのセットで初期化
        Archetype(const std::set<ComponentTypeID>& componentTypes);

        // コンポーネントタイプのセットを取得
        const std::set<ComponentTypeID>& GetComponentTypes() const;

        // アーキタイプの比較演算子（セットを比較）
        bool operator==(const Archetype& other) const;

    private:
        std::set<ComponentTypeID> mComponentTypes; // コンポーネントタイプのセット
    };

}

// ハッシュ関数の定義、std::unordered_mapでArchetypeを使うために必要
namespace std {
    template<>
    struct hash<ECS::Archetype> {
		size_t operator()(const ECS::Archetype& archetype) const { // アーキタイプのハッシュ値を計算
			size_t seed = archetype.GetComponentTypes().size();     // シード値をコンポーネントタイプの数で初期化
			for (auto& type : archetype.GetComponentTypes()) {	 // コンポーネントタイプの数だけループ
				seed ^= type + 0x9e3779b9 + (seed << 6) + (seed >> 2); // ハッシュ値を計算
            }
            return seed;
        }
    };
}