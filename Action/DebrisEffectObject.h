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
    @param	�|�W�V����
    @param	�ړ����x
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
    // ���x�ɑ�����
    const float MovePower;
};

