#pragma once

#include "ComponentType.h"

namespace ECS {

    // �A�[�L�^�C�v��\���N���X
    class Archetype {
    public:
        // �R���X�g���N�^�F�R���|�[�l���g�^�C�v�̃Z�b�g�ŏ�����
        Archetype(const std::set<ComponentTypeID>& componentTypes);

        // �R���|�[�l���g�^�C�v�̃Z�b�g���擾
        const std::set<ComponentTypeID>& GetComponentTypes() const;

        // �A�[�L�^�C�v�̔�r���Z�q�i�Z�b�g���r�j
        bool operator==(const Archetype& other) const;

    private:
        std::set<ComponentTypeID> mComponentTypes; // �R���|�[�l���g�^�C�v�̃Z�b�g
    };

}

// �n�b�V���֐��̒�`�Astd::unordered_map��Archetype���g�����߂ɕK�v
namespace std {
    template<>
    struct hash<ECS::Archetype> {
		size_t operator()(const ECS::Archetype& archetype) const { // �A�[�L�^�C�v�̃n�b�V���l���v�Z
			size_t seed = archetype.GetComponentTypes().size();     // �V�[�h�l���R���|�[�l���g�^�C�v�̐��ŏ�����
			for (auto& type : archetype.GetComponentTypes()) {	 // �R���|�[�l���g�^�C�v�̐��������[�v
				seed ^= type + 0x9e3779b9 + (seed << 6) + (seed >> 2); // �n�b�V���l���v�Z
            }
            return seed;
        }
    };
}