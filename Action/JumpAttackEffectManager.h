#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

class JumpAttackEffectManager :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	_owner �e�N���X�̃|�C���^
    */
    JumpAttackEffectManager(GameObject* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~JumpAttackEffectManager()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    /*
    @fn �G�t�F�N�g���A�N�e�B�u���̏����֐�
    */
    void ActiveEffectProcess();

    /*
    @fn �G�t�F�N�g���Y�����֐�
    */
    void GenerateEffectProcess();


    // �e��GameObject�ۑ��p�ϐ�
    GameObject* owner;
    // particle�̏�ԊǗ��p�ϐ�
    ParticleState particleState;
    // ��������G�t�F�N�g�̃|�W�V����
    Vector3 effectPosition;
    // �t���[���J�E���g�p�ϐ�
    int frameCount;
    // �����������𐔂��邽�߂̃J�E���g
    int generateCount;

};

