#pragma once

#include "System.h"
#include "Entity.h"
#include "Component.h"

namespace ECS {

    class SystemManager {
    public:
        template<typename T>
		std::shared_ptr<T> RegisterSystem();									//�V�X�e���̓o�^

        template<typename T>
		void SetSignature(Signature signature);									//�V�O�l�`���̐ݒ�

		void EntityDestroyed(Entity entity);									//�G���e�B�e�B�̔j��
		void EntitySignatureChanged(Entity entity, Signature entitySignature);	//�G���e�B�e�B�̃V�O�l�`���ύX

    private:
		std::unordered_map<const char*, Signature> signatures{};				//�V�O�l�`���̃}�b�v
		std::unordered_map<const char*, std::shared_ptr<System>> systems{};		//�V�X�e���̃}�b�v
    };

}