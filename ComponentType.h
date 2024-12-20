#pragma once

namespace ECS {

    // �R���|�[�l���g�^�C�v�����ʂ��邽�߂̌^
    using ComponentTypeID = std::size_t;

    inline ComponentTypeID GetUniqueComponentTypeID() {
        static ComponentTypeID lastID = 0u;
        return lastID++;
    }

    // �R���|�[�l���g�^�C�vID���擾����e���v���[�g�֐�
    template<typename T>
    ComponentTypeID GetComponentTypeID() noexcept {
        static ComponentTypeID typeID = GetUniqueComponentTypeID();
        return typeID;
    }

}