#include "EntityManager.h"


// �R���X�g���N�^�F���p�\�ȃG���e�B�e�BID��������
EntityManager::EntityManager() {
	// ���p�\�ȃG���e�B�e�BID��������
	for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
		// �G���e�B�e�BID�𗘗p�\���X�g�ɒǉ�
		mAvailableEntities.push(entity);
	}
}

// �G���e�B�e�B�̐���
Entity EntityManager::CreateEntity() {
	// �G���e�B�e�B�����ő�𒴂��Ȃ����Ƃ��m�F
	assert(mLivingEntityCount < MAX_ENTITIES && "�ő�G���e�B�e�B���𒴂��܂����B");

	// ���p�\��ID����V�����G���e�B�e�BID���擾
	Entity id = mAvailableEntities.front(); // �擪�̃G���e�B�e�BID���擾
	mAvailableEntities.pop();				// �擪�̃G���e�B�e�BID���폜
	++mLivingEntityCount;                   // �G���e�B�e�B���𑝂₷

	return id;
}

// �G���e�B�e�B�̍폜
void EntityManager::DestroyEntity(Entity entity) {
	// �L���ȃG���e�B�e�BID�ł��邱�Ƃ��m�F
	assert(entity < MAX_ENTITIES && "�����ȃG���e�B�e�BID�ł��B");

	// �V�O�l�`�������Z�b�g���AID�𗘗p�\���X�g�ɖ߂�
	mSignatures[entity].reset();        // �V�O�l�`�������Z�b�g
	mAvailableEntities.push(entity);    // ���p�\���X�g�ɖ߂�
	--mLivingEntityCount;               // �G���e�B�e�B�������炷
}

// �G���e�B�e�B�̃V�O�l�`���ݒ�
void EntityManager::SetSignature(Entity entity, Signature signature) {
	// �L���ȃG���e�B�e�BID�ł��邱�Ƃ��m�F
	assert(entity < MAX_ENTITIES && "�����ȃG���e�B�e�BID�ł��B");

	// �w�肳�ꂽ�V�O�l�`�����G���e�B�e�B�ɐݒ�
	mSignatures[entity] = signature;
}

// �G���e�B�e�B�̃V�O�l�`���擾
Signature EntityManager::GetSignature(Entity entity) {
	// �L���ȃG���e�B�e�BID�ł��邱�Ƃ��m�F
	assert(entity < MAX_ENTITIES && "�����ȃG���e�B�e�BID�ł��B");

	// �G���e�B�e�B�̃V�O�l�`����Ԃ�
	return mSignatures[entity];
}
