#include "Archetype.h"

namespace ECS {

	// コンストラクタ：コンポーネントタイプのセットで初期化
    Archetype::Archetype(const std::set<ComponentTypeID>& componentTypes)
        : mComponentTypes(componentTypes) {}

	// コンポーネントタイプのセットを取得
    const std::set<ComponentTypeID>& Archetype::GetComponentTypes() const {
        return mComponentTypes;
    }

	// アーキタイプの比較演算子（セットを比較）
    bool Archetype::operator==(const Archetype& other) const {
        return mComponentTypes == other.mComponentTypes;
    }

}