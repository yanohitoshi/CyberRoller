#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class MeshComponent;
class Mesh;

/*
@file DebrisEffectObject.h
@brief �j�ЃG�t�F�N�g�̍X�V���s��
*/
class DebrisEffectObject :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�e�ƂȂ�N���X�̃|�C���^
    @param	�����x�N�g��
    */
    DebrisEffectObject(const Vector3& _pos, const Vector3& _direction);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~DebrisEffectObject()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    /*
    @fn �������Ԃ̃J�E���g�_�E��
    */
    void LifeCountDown();

    // Mesh���Ǘ�����N���X
    Mesh* mesh;
    // 3D���f���̕`����s���N���X
    MeshComponent* meshComponent;

    // ���g�x�N�g��
    Vector3 direction;
    // ��������
    int lifeCount;
    // �ړ����x
    float moveSpeed;

    // �������Ԃ̍ő�l�萔
    const int MaxLifeCount;
    // ���x�ɑ�����
    const float MovePower;

    // �����_���ȑ��x�𓾂邽�߂̒l
    const int SpeedRandValue;
    // �����_���ȑ��x�̍Œ�l
    const int SpeedLowestValue;

    // �����_���ȉ�]�l�𓾂邽�߂̒l
    const int RotateRandValue;
    // �����_���ȉ�]�l�̍Œ�l
    const int RotateLowestValue;

    // �������x�萔
    const float FallSpeed;
};

