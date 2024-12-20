#pragma once

#include "Entity.h"

namespace ECS {


	//IComponentArray�́A�R���|�[�l���g�z��̊��N���X
	// ���ׂẴR���|�[�l���g�z��́A���̃N���X���p������K�v������
	class IComponentArray {
	public:
		virtual ~IComponentArray() = default;				//�f�X�g���N�^
		virtual void EntityDestroyed(Entity entity) = 0;	//�G���e�B�e�B���j�����ꂽ�Ƃ��ɌĂяo�����
	};


	//�Y���^�I����
	//����ComponentArray<T>�N���X�́AECS�ɂ����āA����̃R���|�[�l���g�^T�ɑΉ����邷�ׂẴG���e�B�e�B�̃R���|�[�l���g���Ǘ����邽�߂̂���

	//���̃e���v���[�g�N���X�́A����̃R���|�[�l���g�̔z���ێ����A�G���e�B�e�B�Ƃ��̃R���|�[�l���g�̃C���f�b�N�X��ǐ�
	template<typename T>
	class ComponentArray : public IComponentArray {
	public:

		//�V�����G���e�B�e�B�ɃR���|�[�l���g��ǉ�
		void InsertData(Entity entity, T component) {

			//�G���e�B�e�B�����ɑ��݂��邩�ǂ������m�F
			assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && "�R���|�[�l���g�͊��ɒǉ�����Ă��܂��B");

			size_t newIndex = size;					 //newIndex�Ɍ��݂�size��ݒ�
			entityToIndexMap[entity] = newIndex;	 //�G���e�B�e�B�Ƃ��̃C���f�b�N�X��o�^
			indexToEntityMap[newIndex] = entity;	 //�C���f�b�N�X�Ƃ��̃G���e�B�e�B��o�^
			componentArray[newIndex] = component;	 //componentArray��newIndex�ʒu�ɃR���|�[�l���g���i�[
			++size;									 //�R���|�[�l���g�̐��𑝂₷
		}

		//�w�肵���G���e�B�e�B����R���|�[�l���g���폜
		//���̊֐��́A�G���e�B�e�B���폜����ꍇ�ɍŌ�̃R���|�[�l���g���ړ����邽�߁A�������ێ�����
		void RemoveData(Entity entity) {

			//�G���e�B�e�B��entityToIndexMap�ɑ��݂��邱�Ƃ��m�F
			assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "�R���|�[�l���g�����݂��܂���B");

			size_t indexOfRemovedEntity = entityToIndexMap[entity];                     //�폜����G���e�B�e�B�̃C���f�b�N�X
			size_t indexOfLastElement = size - 1;                                       //�z��̍Ō�̗v�f�̃C���f�b�N�X
			componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];  //�z��̍Ō�̃R���|�[�l���g���A�폜�Ώۂ̈ʒu�ɏ㏑������B�z��̒��Ԃ̗v�f���폜����ۂ̃M���b�v��h��

			Entity lastEntity = indexToEntityMap[indexOfLastElement];                   //lastEntity���擾���A���̃G���e�B�e�B�̃C���f�b�N�X���X�V
			entityToIndexMap[lastEntity] = indexOfRemovedEntity;						//�G���e�B�e�B�̃C���f�b�N�X���X�V�A�ړ������R���|�[�l���g�̐V�����ʒu�𔽉f
			indexToEntityMap[indexOfRemovedEntity] = lastEntity;						//�C���f�b�N�X�̃G���e�B�e�B���X�V�A�ړ������R���|�[�l���g�̐V�����ʒu�𔽉f

			entityToIndexMap.erase(entity);												//�폜�Ώۂ̃G���e�B�e�B�̃G���g����entityToIndexMap��indexToEntityMap����폜
			indexToEntityMap.erase(indexOfLastElement);									//����

			--size;																		//�R���|�[�l���g�����X�V
		}

		//�w�肵���G���e�B�e�B�Ɋ֘A�t����ꂽ�R���|�[�l���g�ւ̎Q�Ƃ��擾
		T& GetData(Entity entity) {
			//�G���e�B�e�B�����݂��邱�Ƃ��m�F
			assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "�R���|�[�l���g�����݂��܂���B");

			//�G���e�B�e�B�Ɋ֘A�t����ꂽ�R���|�[�l���g�ւ̎Q�Ƃ�Ԃ�
			return componentArray[entityToIndexMap[entity]];//componentArray[entityToIndexMap[entity]]�̓G���e�B�e�B�Ɋ֘A�t����ꂽ�R���|�[�l���g�ւ̎Q��
		}

		//�G���e�B�e�B���R���|�[�l���g�������Ă��邩�ǂ������m�F
		bool HasData(Entity entity) {
			return entityToIndexMap.find(entity) != entityToIndexMap.end();//EntityToIndexMap�ɃG���e�B�e�B�����݂��邩���`�F�b�N���A���̌��ʂ�Ԃ�
		}


		//�G���e�B�e�B���j�����ꂽ�Ƃ��ɁA�֘A����R���|�[�l���g���폜
		void EntityDestroyed(Entity entity) override {
			if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {//�G���e�B�e�B�����݂��邩�ǂ������m�F
				RemoveData(entity);//�G���e�B�e�B�����݂���ꍇ�A�֘A����R���|�[�l���g���폜
			}
		}

	private:
		std::array<T, MAX_ENTITIES> componentArray{};                                    //�Œ�T�C�Y�̔z��ŁA�e�R���|�[�l���g�̃f�[�^���i�[
		std::unordered_map<Entity, size_t> entityToIndexMap{};						     //�G���e�B�e�B����z��̃C���f�b�N�X�ւ̃}�b�s���O��ێ�
		std::unordered_map<size_t, Entity> indexToEntityMap{};						     //�z��̃C���f�b�N�X����G���e�B�e�B�ւ̃}�b�s���O��ێ�
		size_t size{};  													             //�R���|�[�l���g�̐�
	};

}