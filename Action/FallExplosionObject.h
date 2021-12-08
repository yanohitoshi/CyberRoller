#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ExplosionObjectBase.h"

// �N���X�̑O���錾
class MeshComponent;
class Mesh;
class BoxCollider;
class ExplosionObjectStateBase;
class FallExplosionArea;
enum class ExplosionObjectState;

/*
@file FallExplosionObject.h
@brief �������锚�����I�u�W�F�N�g
*/
class FallExplosionObject :
    public ExplosionObjectBase
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�e�N���X�̃|�C���^
	@param	�|�W�V����
	@param	�I�u�W�F�N�g���ʗptag
	*/
	FallExplosionObject(FallExplosionArea* _owner, const Vector3& _pos, const Tag _objectTag);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~FallExplosionObject()override;

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
	@param	�����蔻��^�O
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	// �I�[�i�[�ƂȂ锚���������G���A�N���X�̃|�C���^�ϐ�
	FallExplosionArea* owner;

};