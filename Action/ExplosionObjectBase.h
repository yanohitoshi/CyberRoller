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
	@param	�I�u�W�F�N�g���ʗptag
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

	// �I�u�W�F�N�g�̌��݂̃X�e�[�^�X
	ExplosionObjectState nowState;
	// �I�u�W�F�N�g�̎��̃X�e�[�^�X
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
	// �����������̓��������I�u�W�F�N�g�̃|�W�V����
	Vector3 hitPosition;
	// �����|�W�V����
	Vector3 firstPosition;
	// �~��G���A
	Vector3 fallArea;

	// �������x
	float fallSpeed;

	// �Sstate���i�[�����}�b�v
	std::unordered_map<ExplosionObjectState, ExplosionObjectStateBase*> statePoolMap;

public:

	/*
	@fn meshComponent��getter
	@return meshComponent�̃|�C���^
	*/
	MeshComponent* GetMeshComponent() { return meshComponent; }

	/*
	@brief�@�����������t���O��getter
	@return	isExplode
	*/
	bool GetIsExplode() { return isExplode; }
	
	/*
	@brief�@�����J�n��Ԃ��t���O��getter
	@return	isStartExplosion
	*/
	bool GetIsStartExplosion() { return isStartExplosion; }
	
	/*
	@brief�@�q�b�g�������肪�W�����v�A�^�b�N��Ԃ̃v���C���[���ǂ����t���O��getter
	@return	isHitJumpAttackPlayer
	*/
	bool GetIsHitJumpAttackPlayer() { return isHitJumpAttackPlayer; }
	
	/*
	@brief�@��������I�u�W�F�N�g�ɓ����������t���O��getter
	@return	isHitExplosionObject
	*/
	bool GetIsHitExplosionObject() { return isHitExplosionObject; }

	/*
	@brief�@�����J�n���邩�t���O��getter
	@return	isFallStart
	*/
	bool GetIsFallStart() { return isFallStart; }

	/*
	@brief�@�����������̓��������I�u�W�F�N�g�̃|�W�V������getter
	@return	hitPosition
	*/
	Vector3 GetHitPosition() { return hitPosition; }
	
	/*
	@brief�@�~��G���A��getter
	@return	fallArea
	*/
	Vector3 GetFallArea() { return fallArea; }
	
	/*
	@brief�@�����|�W�V������getter
	@return	firstPosition
	*/
	Vector3 GetFirstPosition() { return firstPosition; }

	/*
	@brief�@�������x��getter
	@return	fallSpeed
	*/
	float GetFallSpeed() { return fallSpeed; }

	/*
	@brief isExplode��setter�֐�
	@param	_isExplode �������Ă��邩
	*/
	void SetIsExplode(bool _isExplode) { isExplode = _isExplode; }
	
	/*
	@brief isStartExplosion��setter�֐�
	@param	_isStartExplosion �����J�n��Ԃ�
	*/
	void SetIsStartExplosion(bool _isStartExplosion) { isStartExplosion = _isStartExplosion; }
	
	/*
	@brief isHitExplosionObject��setter�֐�
	@param	_isHitExplosionObject ��������I�u�W�F�N�g�ɐG�ꂽ��
	*/
	void SetIsHitExplosionObject(bool _isHitExplosionObject) { isHitExplosionObject = _isHitExplosionObject; }

	/*
	@brief fallSpeed��setter�֐�
	@param	_fallSpeed �������x
	*/
	void SetFallSpeed(float _fallSpeed) { fallSpeed = _fallSpeed; }
};

