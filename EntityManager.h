#pragma once



// �G���e�B�e�B��ID��\���^��`
using Entity = uint32_t;

// �ő�G���e�B�e�B���̒�`
const Entity MAX_ENTITIES = 50000;

//�R���|�[�l���g�̍ő吔���w��
const uint32_t MAX_COMPONENTS = 32;

// �V�O�l�`���̒�`�i�r�b�g�Z�b�g�ŃR���|�[�l���g�̗L�����Ǘ��j
using Signature = std::bitset<MAX_COMPONENTS>;//�r�b�g�Z�b�g�ŃR���|�[�l���g�̗L�����Ǘ��i�r�b�g�������Ă���ƃR���|�[�l���g�����݂���j

class EntityManager {
public:
    // �R���X�g���N�^�F���p�\�ȃG���e�B�e�BID��������
    EntityManager();

    // �G���e�B�e�B�̐���
    Entity CreateEntity();

	// �G���e�B�e�B�̍폜�i�����̓G���e�B�e�BID�j
    void DestroyEntity(Entity entity);

	// �G���e�B�e�B�̃V�O�l�`���ݒ�i�����̓G���e�B�e�BID ,�V�O�l�`���j
    void SetSignature(Entity entity, Signature signature);

	// �G���e�B�e�B�̃V�O�l�`���擾�i�����̓G���e�B�e�BID�j
    Signature GetSignature(Entity entity);

private:
    // ���p�\�ȃG���e�B�e�BID���Ǘ�����L���[
    std::queue<Entity> mAvailableEntities{};

    // �G���e�B�e�B���Ƃ̃V�O�l�`�����Ǘ�����z��
    std::array<Signature, MAX_ENTITIES> mSignatures{};

    // ���݂̃G���e�B�e�B��
    uint32_t mLivingEntityCount{};
};