#pragma once

#include "Entity.h"
#include "Component.h"

namespace ECS {

	// �G���e�B�e�B�}�l�[�W���i�G���e�B�e�B�̐����A�폜�A�V�O�l�`���̐ݒ�j
    class EntityManager {
    public:
		EntityManager();                                        // �R���X�g���N�^

		Entity CreateEntity();								    // �G���e�B�e�B�̐���
		void DestroyEntity(Entity entity);					    // �G���e�B�e�B�̍폜

		void SetSignature(Entity entity, Signature signature);  //�G���e�B�e�B�̃V�O�l�`���ݒ�
        Signature GetSignature(Entity entity) const;

    private:
		std::queue<Entity> availableEntities{};                 // ���p�\�ȃG���e�B�e�BID�̃L���[
		std::array<Signature, MAX_ENTITIES> signatures{};		// �G���e�B�e�B�̃V�O�l�`��
		uint32_t livingEntityCount{};							// ���݂̃G���e�B�e�B��
    };

}