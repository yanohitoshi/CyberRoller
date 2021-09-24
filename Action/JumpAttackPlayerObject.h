#pragma once
#include "GameObject.h"

class MeshComponent;
class PlayerObject;
class SphereCollider;

class JumpAttackPlayerObject :
    public GameObject
{
public:
	
	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	�ė��p���邩�t���O
	@param	�I�u�W�F�N�g���ʗptag
	*/
	JumpAttackPlayerObject(PlayerObject* _ownerObject, const Vector3& _size, const Tag _objectTag);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~JumpAttackPlayerObject();

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

private:

    MeshComponent* meshComponent;
	PlayerObject* ownerObject;
	SphereCollider* sphereCollider;

	// ��]����ۂ̊p�x
	float rotationAngle;
	// ��]�p�ɑ���������l�萔
	const float Rotation;
	State tmpState;

};

