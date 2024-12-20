#include "Archetype.h"

namespace ECS {

	// �R���X�g���N�^�F�R���|�[�l���g�^�C�v�̃Z�b�g�ŏ�����
    Archetype::Archetype(const std::set<ComponentTypeID>& componentTypes)
        : mComponentTypes(componentTypes) {}

	// �R���|�[�l���g�^�C�v�̃Z�b�g���擾
    const std::set<ComponentTypeID>& Archetype::GetComponentTypes() const {
        return mComponentTypes;
    }

	// �A�[�L�^�C�v�̔�r���Z�q�i�Z�b�g���r�j
    bool Archetype::operator==(const Archetype& other) const {
        return mComponentTypes == other.mComponentTypes;
    }

}