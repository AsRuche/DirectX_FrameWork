#pragma once

#include "System.h"
#include "Entity.h"
#include "Component.h"

namespace ECS {

    class SystemManager {
    public:
        template<typename T>
		std::shared_ptr<T> RegisterSystem();									//システムの登録

        template<typename T>
		void SetSignature(Signature signature);									//シグネチャの設定

		void EntityDestroyed(Entity entity);									//エンティティの破棄
		void EntitySignatureChanged(Entity entity, Signature entitySignature);	//エンティティのシグネチャ変更

    private:
		std::unordered_map<const char*, Signature> signatures{};				//シグネチャのマップ
		std::unordered_map<const char*, std::shared_ptr<System>> systems{};		//システムのマップ
    };

}