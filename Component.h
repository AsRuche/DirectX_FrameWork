#pragma once

namespace ECS {

	using ComponentType = std::uint8_t;			 // �R���|�[�l���g�^�C�v��\���^��`
	const ComponentType MAX_COMPONENTS = 32;	 // �ő�R���|�[�l���g�^�C�v��
	using Signature = std::bitset<MAX_COMPONENTS>; // �V�O�l�`����\���r�b�g�Z�b�g

}