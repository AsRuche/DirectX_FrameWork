#pragma once
#include "ComponentType.h"
namespace ECS {
    class ComponentInfo {
    public:
        template<typename T>
        static void RegisterComponent() {
            ComponentTypeID typeID = GetComponentTypeID<T>();
            mComponentSizes[typeID] = sizeof(T);
        }
        static size_t GetComponentSize(ComponentTypeID typeID) {
            return mComponentSizes[typeID];
        }
    private:
        static std::unordered_map<ComponentTypeID, size_t> mComponentSizes;
    };
}