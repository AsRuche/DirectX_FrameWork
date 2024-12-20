#pragma once

namespace ECS {

    // コンポーネントタイプを識別するための型
    using ComponentTypeID = std::size_t;

    inline ComponentTypeID GetUniqueComponentTypeID() {
        static ComponentTypeID lastID = 0u;
        return lastID++;
    }

    // コンポーネントタイプIDを取得するテンプレート関数
    template<typename T>
    ComponentTypeID GetComponentTypeID() noexcept {
        static ComponentTypeID typeID = GetUniqueComponentTypeID();
        return typeID;
    }

}