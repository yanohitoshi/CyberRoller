#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class MeshComponent;
class Mesh;
class BoxCollider;
class ExplosionObjectStateBase;
enum class ExplosionObjectState;

/*
@file ExplosionObjectBase.h
@brief ��������I�u�W�F�N�g�̊��N���X
*/
class ExplosionObjectBase :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	�I�u�W�F�N�g���ʗptag
	@param	�ړ����x
	@param	�ǐՂ���I�u�W�F�N�g�̃|�C���^
	@param	�ǐՃG���A�̒l
	*/
	ExplosionObjectBase(const Tag _objectTag);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	virtual ~ExplosionObjectBase() {};

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	virtual void UpdateGameObject(float _deltaTime) {};

	/*
	@fn �߂荞�ݔ���
	*/
	virtual void FixCollision(AABB& myAABB, const AABB& pairAABB) {};

protected:

	/*
	@brief �X�e�[�g�v�[���p�}�b�v�ɃX�e�[�g�N���X��ǉ�����֐�
	@param	_state �ǉ�����X�e�[�g�N���X�̃|�C���^
	@param	_stateTag ���ƂȂ�^�O
	*/
	void AddStatePoolMap(ExplosionObjectStateBase* _state, ExplosionObjectState _stateTag);

	/*
	@brief �X�e�[�g�v�[���p�}�b�v����X�e�[�g�N���X���폜����֐�
	@param	_stateTag ���ƂȂ�^�O
	*/
	void RemoveStatePoolMap(ExplosionObjectState _stateTag);

	/*
	@brief �X�e�[�g�v�[���p�}�b�v���N���A����
	*/
	void ClearStatePoolMap();

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	@param	�����蔻��^�O
	*/
	virtual void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag) {};

	// Mesh�̓ǂݍ��݂��s���N���X
	Mesh* mesh;
	// 3D���f���̕`����s���N���X
	MeshComponent* meshComponent;
	// AABB�̓����蔻����s���N���X
	BoxCollider* boxCollider;

	ExplosionObjectState nowState;
	ExplosionObjectState nextState;

	// �����J�n��Ԃ�
	bool isStartExplosion;
	// ����������
	bool isExplode;
	// ��������I�u�W�F�N�g�ɓ���������
	bool isHitExplosionObject;
	// �q�b�g�������肪�W�����v�A�^�b�N��Ԃ̃v���C���[���ǂ���
	bool isHitJumpAttackPlayer;
	// �����J�n���邩
	bool isFallStart;
	// �v���C���[�������������̃v���C���[�̃|�W�V����
	Vector3 hitPosition;
	// �����|�W�V����
	Vector3 firstPosition;
	// �~��G���A
	Vector3 fallArea;

	float fallSpeed;

	// �Sstate���i�[�����}�b�v
	std::unordered_map<ExplosionObjectState, ExplosionObjectStateBase*> statePoolMap;

public:

	MeshComponent* GetMeshComponent() { return meshComponent; }

	bool GetIsExplode() { return isExplode; }
	bool GetIsStartExplosion() { return isStartExplosion; }
	bool GetIsHitJumpAttackPlayer() { return isHitJumpAttackPlayer; }
	bool GetIsHitExplosionObject() { return isHitExplosionObject; }
	bool GetIsFallStart() { return isFallStart; }

	Vector3 GetHitPosition() { return hitPosition; }
	Vector3 GetFallArea() { return fallArea; }
	Vector3 GetFirstPosition() { return firstPosition; }

	float GetFallSpeed() { return fallSpeed; }

	void SetIsExplode(bool _isExplode) { isExplode = _isExplode; }
	void SetIsStartExplosion(bool _isStartExplosion) { isStartExplosion = _isStartExplosion; }
	void SetIsHitExplosionObject(bool _isHitExplosionObject) { isHitExplosionObject = _isHitExplosionObject; }

	void SetFallSpeed(float _fallSpeed) { fallSpeed = _fallSpeed; }
};

