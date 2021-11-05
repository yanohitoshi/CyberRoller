#pragma once
#include "GameObject.h"

class MeshComponent;
class Mesh;
class BoxCollider;
class ExplosionObjectStateBase;
enum class ExplosionObjectState;

class ExplosionObject :
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
	ExplosionObject(const Vector3& _pos, const Tag _objectTag);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~ExplosionObject()override;

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

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
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

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
	// �v���C���[�������������̃v���C���[�̃|�W�V����
	Vector3 hitPosition;
	// �����|�W�V����
	Vector3 firstPosition;

	// �Sstate���i�[�����}�b�v
	std::unordered_map<ExplosionObjectState, ExplosionObjectStateBase*> statePoolMap;

public:

	MeshComponent* GetMeshComponent() { return meshComponent; }

	bool GetIsExplode() { return isExplode; }
	bool GetIsStartExplosion() { return isStartExplosion; }
	bool GetIsHitJumpAttackPlayer() { return isHitJumpAttackPlayer; }
	bool GetIsHitExplosionObject() { return isHitExplosionObject; }
	Vector3 GetHitPosition() { return hitPosition; }
	Vector3 GetFirstPosition() { return firstPosition; }

	void SetIsExplode(bool _isExplode) { isExplode = _isExplode; }
	void SetIsStartExplosion(bool _isStartExplosion) { isStartExplosion = _isStartExplosion; }
	void SetIsHitExplosionObject(bool _isHitExplosionObject) { isHitExplosionObject = _isHitExplosionObject; }
};

