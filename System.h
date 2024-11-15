#pragma once

#include "Entity.h"


namespace ECS {

    class System {
    public:
		std::set<Entity> entities;//エンティティの集合
    };

}