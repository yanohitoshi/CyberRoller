#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class MeshComponent;
class BoxCollider;
class Mesh;
class GeometryInstanceComponent;

/*
@file JumpSwitchObject.h
@brief JumpSwitch�̐����ƍX�V���s��
*/
class JumpSwitchObject :
    public GameObject
{

public:

    /*
    @fn �R���X�g���N�^
    @param	�|�W�V����
    @param	object�̃T�C�Y
    @param	�I�u�W�F�N�g���ʗptag
    */
    JumpSwitchObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag);
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~JumpSwitchObject()override;
    
    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    
    /*
    @fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
    @param	��������GameObject
    @param	��������GameObject�̓����蔻��^�O
    */
    void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;
    // 3D���f���̕`����s���N���X
    Mesh* mesh;
    GeometryInstanceComponent* geometryInstanceComponent;
    // �����蔻����s���N���X
    BoxCollider* boxCollider;

};
