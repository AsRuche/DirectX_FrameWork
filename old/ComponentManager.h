#pragma once

#include "ComponentArray.h"

namespace ECS {

	class ComponentManager {
	public:
		template<typename T>
		void RegisterComponent();

		template<typename T>
		ComponentType GetComponentType();

		template<typename T>
		void AddComponent(Entity entity, T component);

		template<typename T>
		void RemoveComponent(Entity entity);

		template<typename T>
		T& GetComponent(Entity entity);

		template<typename T>
		bool HasComponent(Entity entity);

		void EntityDestroyed(Entity entity);

	private:
		std::unordered_map<const char*, ComponentType> componentTypes{}; //�R���|�[�l���g�^�C�v���i�^��񂩂�擾����������j��������I�ȃR���|�[�l���g�^�C�vID�ւ̃}�b�v��ێ�
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays{};//�R���|�[�l���g�^�C�v������A���ꂼ��̃R���|�[�l���g�z��iComponentArray�j�ւ̋��L�|�C���^��ێ�
		ComponentType nextComponentType{};//�V�����R���|�[�l���g�^�C�vID�����蓖�Ă邽�߂̃J�E���^

		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray();
	};

}


//�e���v���[�g�֐��̎���
namespace ECS {


	//�R���|�[�l���g�̓o�^���s���֐�
	template<typename T>
	void ComponentManager::RegisterComponent() {
		const char* typeName = typeid(T).name();//�R���|�[�l���g�̌^�����擾

		//�R���|�[�l���g�^�C�v���o�^����Ă��Ȃ����Ƃ��m�F
		assert(componentTypes.find(typeName) == componentTypes.end() && "�R���|�[�l���g�^�C�v�͊��ɓo�^����Ă��܂��B");

		componentTypes[typeName] = nextComponentType;//�V�����R���|�[�l���g�^�C�vID��o�^
		componentArrays[typeName] = std::make_shared<ComponentArray<T>>();//componentArrays�ɐV����componentArray<T>�̃C���X�^���X���쐬���ēo�^

		++nextComponentType;//���̃R���|�[�l���g�^�C�vID���X�V
	}

	//�R���|�[�l���g�^�C�v�̎擾
	template<typename T>
	ComponentType ComponentManager::GetComponentType() {
		const char* typeName = typeid(T).name();//�R���|�[�l���g�̌^�����擾

		//�R���|�[�l���g�^�C�v���o�^����Ă��邱�Ƃ��m�F
		assert(componentTypes.find(typeName) != componentTypes.end() && "�R���|�[�l���g�^�C�v���o�^����Ă��܂���B");

		//�R���|�[�l���g�^�C�vID��Ԃ�
		return componentTypes[typeName];
	}

	//����̃G���e�B�e�B�ɑ΂��ăR���|�[�l���gT��ǉ�
	template<typename T>
	void ComponentManager::AddComponent(Entity entity, T component) {
		GetComponentArray<T>()->InsertData(entity, component);//�擾�����z���InsertData(entity, component)���Ăяo���āA�G���e�B�e�B�ƃR���|�[�l���g��ǉ�
	}

	//����̃G���e�B�e�B����R���|�[�l���gT���폜
	template<typename T>
	void ComponentManager::RemoveComponent(Entity entity) {//�擾�����z���RemoveData(entity)���Ăяo���āA�G���e�B�e�B����R���|�[�l���g���폜
		GetComponentArray<T>()->RemoveData(entity);//�擾�����z���RemoveData(entity)���Ăяo���āA�G���e�B�e�B����R���|�[�l���g���폜
	}

	//��̃G���e�B�e�B�ɕR�Â��R���|�[�l���gT���擾
	template<typename T>
	T& ComponentManager::GetComponent(Entity entity) {
		return GetComponentArray<T>()->GetData(entity); //GetComponentArray<T>()�ŃR���|�[�l���g�z����擾�B�z���GetData(entity)���Ăяo���āA�R���|�[�l���g���擾
	}

	//����̃G���e�B�e�B���R���|�[�l���gT�������Ă��邩�ǂ������m�F
	template<typename T>
	bool ComponentManager::HasComponent(Entity entity) {
		return GetComponentArray<T>()->HasData(entity);//�擾�����z���HasData(entity)���Ăяo���āA�G���e�B�e�B���R���|�[�l���g�������Ă��邩�ǂ������m�F
	}

	//�����Ŏg�p�����A����̃R���|�[�l���g�^�C�vT�ɑΉ�����R���|�[�l���g�z����擾
	template<typename T>
	std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray() {
		const char* typeName = typeid(T).name();//�R���|�[�l���g�̌^�����擾

		assert(componentTypes.find(typeName) != componentTypes.end() && "�R���|�[�l���g�^�C�v���o�^����Ă��܂���B");//�R���|�[�l���g�^�C�v���o�^����Ă��邱�Ƃ��m�F

		return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]); //componentArrays����R���|�[�l���g�z����擾���Astd::static_pointer_cast��ComponentArray<T>�ɃL���X�g���ĕԂ�
	}

	//�G���e�B�e�B���폜���ꂽ�ۂɁA���̃G���e�B�e�B�Ɋ֘A���邷�ׂẴR���|�[�l���g���폜
	inline void ComponentManager::EntityDestroyed(Entity entity) {
		for (auto const& pair : componentArrays) {//componentArrays�ɓo�^����Ă��邷�ׂẴR���|�[�l���g�z������ɏ���
			auto const& component = pair.second;//�R���|�[�l���g�z����擾

			component->EntityDestroyed(entity); //�e�z��ɑ΂���EntityDestroyed(entity)���Ăяo���A�G���e�B�e�B�Ɋ֘A����f�[�^���폜
		}
	}

}