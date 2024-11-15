#pragma once

#include "Entity.h"

namespace ECS {

	// �R���|�[�l���g�z��̃C���^�[�t�F�[�X
    class IComponentArray {
    public:
		virtual ~IComponentArray() = default;                   // �f�X�g���N�^
    };

    template<typename T>
    class ComponentArray : public IComponentArray {
    public:
		void InsertData(Entity entity, T component);            // �f�[�^�̑}��
		void RemoveData(Entity entity);						    // �f�[�^�̍폜
		T& GetData(Entity entity);							    // �f�[�^�̎擾
		bool HasData(Entity entity);							// �f�[�^�̗L��

    private:
		std::array<T, MAX_ENTITIES> componentArray{};		    //�R���|�[�l���g�̔z��
		std::unordered_map<Entity, size_t> entityToIndexMap{};   //�G���e�B�e�BID����C���f�b�N�X�ւ̃}�b�v
		std::unordered_map<size_t, Entity> indexToEntityMap{};   //�C���f�b�N�X����G���e�B�e�BID�ւ̃}�b�v
		size_t size{ 0 };									   //�R���|�[�l���g�̃T�C�Y
    };

}