#pragma once
#include "GameObject.h"

// class�̑O�u�錾
class SkeletalMeshComponent;
class Animation;
class BoxCollider;
class Mesh;
enum class EnemyState;

class EnemyObjectBase :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@brief �ʏ�̃G�l�~�[�̃R���X�g���N�^
	@param	�|�W�V����
	@param	�ė��p���邩�t���O
	@param	�I�u�W�F�N�g���ʗptag
	*/
	EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag);

	/*
	@fn �R���X�g���N�^
	@brief �ړ�����G�l�~�[�̃R���X�g���N�^
	@param	�|�W�V����
	@param	�ė��p���邩�t���O
	@param	�I�u�W�F�N�g���ʗptag
	@param	�ړ����x
	@param	�ړ�����
	@param	�ړ�����
	*/
	EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag,float _moveSpeed,const Vector3& _moveDirection, float _moveDistance);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	virtual ~EnemyObjectBase() {};

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

	/*
	@fn �����߂�����
	*/
	void EnemyCalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);

protected:

	// 3D���f���̕`����s���N���X
	SkeletalMeshComponent* skeltalMeshComponent;
	// Mesh�̓ǂݍ��݂��s���N���X
	Mesh* mesh;
	// AABB�̓����蔻����s���N���X
	BoxCollider* boxCollider;
	// �G�l�~�[��AABB�\����
	AABB enemyBox;

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	*/
	virtual void OnCollision(const GameObject& _hitObject) {};

	//�E�����x�N�g��
	Vector3 rightVec;
	//�L�����N�^�[�̑O���x�N�g��
	Vector3 charaForwardVec;
	//�����ɍ��킹�ĉ�]�����邽�߂̃x�N�g��
	Vector3 rotateVec;

	Vector3 firstPosition;
	// ���x
	float moveSpeed;

	// �ړ�����
	Vector3 moveDirection;

	// �ړ�����
	float moveDistance;

	//�ڒn�t���O
	bool onGround;

	// ����ł��邩�ǂ���
	bool isDeadFlag;

	// ���̃v���[���[��state��Ԃ�ۑ����邽�߂̕ϐ�
	EnemyState nowState;
	// �ύX���ꂽ���̃v���[���[��state��Ԃ�ۑ����邽�߂̕ϐ�
	EnemyState nextState;

	// Animation�v�[��
	std::vector<const Animation*> animTypes;
	// state�v�[��
	std::vector<class EnemyObjectStateBase*> statePools;

private:



public:// �Q�b�^�[�Z�b�^�[

	/*
	@fn skeltalMeshComponent��getter�֐�
	@return SkeletalMeshComponent�@SkeletalMeshComponent�N���X�̃|�C���^��Ԃ�
	*/
	SkeletalMeshComponent* GetSkeletalMeshComponent() { return skeltalMeshComponent; }

	/*
	@fn Animation��getter�֐�
	@param _state ���݂̃v���C���[�̃X�e�[�^�X
	@return Animation Animation�N���X�̃|�C���^��Ԃ�
	*/
	const Animation* GetAnimation(EnemyState _state);

	/*
	@fn forwardVec��getter�֐�
	@return forwardVec��Ԃ�
	*/
	Vector3 GetForwardVec() { return forwardVec; }

	/*
	@fn rightVec��getter�֐�
	@return rightVec��Ԃ�
	*/
	Vector3 GetRightVec() { return rightVec; }

	/*
	@fn charaForwardVec��getter�֐�
	@return charaForwardVec��Ԃ�
	*/
	Vector3 GetCharaForwardVec() { return charaForwardVec; }

	/*
	@fn rotateVec��getter�֐�
	@return rotateVec��Ԃ�
	*/
	Vector3 GetRotateVec() { return rotateVec; }

	/*
	@fn velocity��getter�֐�
	@return velocity��Ԃ�
	*/
	Vector3 GetVelocity() { return velocity; }

	/*
	@fn moveDirection��getter�֐�
	@return moveDirection��Ԃ�
	*/
	Vector3 GetMoveDirection() { return moveDirection; }

	/*
	@fn firstPosition��getter�֐�
	@return firstPosition��Ԃ�
	*/
	Vector3 GetFirstPosition() { return firstPosition; }

	/*
	@fn moveDistance��getter�֐�
	@return moveDistance��Ԃ�
	*/
	float GetMoveDistance() { return moveDistance; }

	/*
	@fn moveSpeed��getter�֐�
	@return moveSpeed��Ԃ�
	*/
	float GetMoveSpeed() { return moveSpeed; }

	/*
	@fn onGround��getter�֐�
	@return onGround��Ԃ�
	*/
	bool GetOnGround() { return onGround; }

	/*
	@fn nowState��getter�֐�
	@return nowState��Ԃ�
	*/
	EnemyState GetNowState() { return nowState; }

	/*
	@fn charaForwardVec��setter�֐�
	@param	Vector3 _charaForwardVec �L�����N�^�[�̑O���x�N�g��
	*/
	void SetCharaForwardVec(Vector3 _charaForwardVec) { charaForwardVec = _charaForwardVec; }

	/*
	@fn velocity��setter�֐�
	@param	Vector3 _velocity �L�����N�^�[�̑��x�x�N�g��
	*/
	void SetVelocity(Vector3 _velocity) { velocity = _velocity; }

	/*
	@fn velocity��setter�֐�
	@param	Vector3 _moveDirection �L�����N�^�[�̈ړ������x�N�g��
	*/
	void SetMoveDirection(Vector3 _moveDirection) { moveDirection = _moveDirection; }

	/*
	@fn moveDistance��setter�֐�
	@param	float moveDistance �L�����N�^�[�̈ړ�����
	*/
	void SetMoveDistance(float _moveDistance) { moveDistance = _moveDistance; }

	/*
	@fn moveSpeed��setter�֐�
	@param	float _moveSpeed �L�����N�^�[�̃X�s�[�h
	*/
	void SetMoveSpeed(float _moveSpeed) { moveSpeed = _moveSpeed; }

	/*
	@fn isDeadFlag��Gettrer�֐�
	@return	bool isDeadFlag ���S���
	*/
	bool GetIsDeadFlag() { return isDeadFlag; }

	/*
	@fn isDeadFlag��setter�֐�
	@param	bool isDeadFlag ���S���
	*/
	void SetIsDeadFlag(bool _isDeadFlag) { isDeadFlag = _isDeadFlag; }
};

