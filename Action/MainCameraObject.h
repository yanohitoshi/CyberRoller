#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "CameraObjectBase.h"
#include "PlayerObject.h"

// �N���X�̑O���錾
class BoxCollider;

/*
@file MainCameraObject.h
@brief �蓮�ŉ�]�����邱�Ƃ��o����J�����N���X
*/
class MainCameraObject :
	public CameraObjectBase
{
public:

	/*
	@brief	�R���X�g���N�^
	@param	�|�W�V����
	@param	�v���C���[�̃|�C���^
	*/
	MainCameraObject(const Vector3 _pos, PlayerObject* _playerObject);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~MainCameraObject();

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime = 1.0f)override;
	
	/*
	@fn ���͂������Ŏ󂯎��X�V�֐�
	@brief ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
	@param	_keyState ���͏��
	*/
	void GameObjectInput(const InputState& _keyState)override;

	/*
	@brief	����Ώە��̏��𓾂�
	@param _offset�@���������W�Ƃ̍�
	@param _parentPos�@������W
	*/
	void SetViewMatrixLerpObject(const Vector3& _offset, const Vector3& _parentPos);

	/*
	@brief �����߂����s��
	@param ������AABB
	@param �����AABB
	@param �y�A�ƂȂ鑊���Tag
	*/
	void FixCollision(AABB& myAABB, const AABB& pairAABB);

	/*
	@brief �����߂��v�Z���s��
	@param ������AABB
	@param �����AABB
	@param �����߂���
	*/
	void CalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);
	
	/*
	@brief �ǐՂ���ΏۃI�u�W�F�N�g�̃|�W�V������getter
	@param �ǐՂ���ΏۃI�u�W�F�N�g�|�W�V����
	*/
	Vector3 GetlerpObjectPos() { return lerpObjectPos; }

private:

	/*
	@brief �Q�[�����̈ړ�����
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void InGameMovableProcess(float _deltaTime);
	
	/*
	@brief ���a�␳�v�Z����
	*/
	void CorrectionRadius();
	
	/*
	@brief �s�b�`�␳�v�Z����
	*/
	void CorrectionPitch();

	/*
	@brief �|�W�V�����v�Z����
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void CalculationPosition(float _deltaTime);

	/*
	@brief �r���[�s��v�Z����
	*/
	void CalculationViewMatrix();

	/*
	@brief �Q�[���N���A���̏���
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void GameClearProcess(float _deltaTime);

	/*
	@brief �Q�[���I�[�o�[���̏���
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void GameOverProcess(float _deltaTime);
	
	/*
	@brief �v���C���[���_���X��Ԃ̎��̏���
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void PlayerInDanceProcess(float _deltaTime);
	
	/*
	@brief ���̓`�F�b�N�Ƃ��̏���
	@param	_keyState ���͏��
	*/
	void CheckInputProcess(const InputState& _keyState);

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	@param	��������GameObject�̓����蔻��^�O
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	// AABB�̏��������̍ő�l�萔
	const Vector3 AabbInitMax;
	// AABB�̏��������̍ŏ��l�萔
	const Vector3 AabbInitMin;

	// �J�����̃��[�̈ړ����x
	const float YawSpeed;
	// �J�����̃s�b�`�̈ړ����x
	const float PitchSpeed;
	// ������]����ۂ̈ړ����x
	const float AutomaticMoveSpeed;

	// �J�����̍����̍ő�l
	const float MaxPitch;
	// �J�����̍����̍ŏ��l
	const float MinPitch;

	// �J�������a�̍ő�l
	const float MaxRadius;
	// �J�������a�̒��ԓ_�̒l
	const float MediumRadius;
	// �J�������a�̍ŏ��l
	const float MinRadius;
	// �^�C���I�[�o�[���̔��a
	const float TimeOverRadius;
	// �_���X����Ԏ��̔��a
	const float DanceRadius;
	// ����Ώە����瓖�������ꏊ�������Ē��������ۂ̕␳�萔
	const float CorrectionBackRadius;

	// ������𒍎�����悤�ɂ������̂�Z�������炷�萔
	const float ShiftGazePoint;

	//�e�I�u�W�F�N�g�Ƃ̍�
	Vector3 offsetPos;

	// �����߂����s������Ɠ��������ʒu��ۑ�����Vector3�ϐ�
	Vector3 hitPosition;

	// �����蔻����s���N���X(AABB/����)
	BoxCollider* boxcollider;

	//�Ǐ]��̃I�u�W�F�N�g���������Ă��邩
	bool hasParentObject;

	// �����߂����s������Ɠ����������𔻒肷��t���O
	bool hitFlag;

	// �O�̃t���[���ŉ����߂����s������Ɠ����������𔻒肷��t���O
	bool tmpHitFlag;

	//�J�����̍���
	float height;

	//�J������]�̔��a
	float radius;

};

