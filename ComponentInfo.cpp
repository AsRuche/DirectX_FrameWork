#include "ComponentInfo.h"
namespace ECS {
	std::unordered_map<ComponentTypeID, size_t> ComponentInfo::mComponentSizes;
}