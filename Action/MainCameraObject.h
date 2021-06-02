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
@brief ���C���J���� �Q�[�����̃I�u�W�F�N�g���f��
*/
class MainCameraObject :
	public CameraObjectBase
{
public:
	/*
	@brief	�R���X�g���N�^
	@param	�|�W�V����
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
	void calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);
	
	/*
	@brief	player�ȊO�̂��̂𒍎�����ۂɎg��setter
	@param ����Ώە��̃|�W�V����
	*/
	void SetLerpObjectPos(const Vector3& _pos) { lerpObjectPos = _pos; }
	
	/*
	@brief �J�����̑O���x�N�g���𓾂邽�߂�getter
	@param �J�����̑O���x�N�g��
	*/
	Vector3 GetCameraVec() { return forwardVec; }
	

	/*
	@brief �ǐՂ���ΏۃI�u�W�F�N�g�̃|�W�V������getter
	@param �ǐՂ���ΏۃI�u�W�F�N�g�|�W�V����
	*/
	Vector3 GetlerpObjectPos() { return lerpObjectPos; }

	/*
	@brief ���X�|�[�������Ƃ��ɃJ�����̈ʒu��������ԂɃZ�b�g����֐�
	*/
	void ReSetYaw() { yaw = Math::ToRadians(180); }

	//�Ǐ]��̃I�u�W�F�N�g���W
	Vector3 lerpObjectPos;

private:

	void InGameMovableProcess(float _deltaTime);

	void CorrectionRadius();

	void CorrectionPitch();

	void CalculationPosition(float _deltaTime);

	void CalculationViewMatrix();

	void GameClearProcess(float _deltaTime);

	void GameOverProcess(float _deltaTime);

	void PlayerInDanceProcess(float _deltaTime);

	void ChackInputProcess(const InputState& _keyState);

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

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

	// ���`�ۊǎ��Ƀf���^�^�C����������Ƃ��p�̕␳�萔
	const float DeltaCorrection;

	// ������𒍎�����悤�ɂ������̂�Z�������炷�萔
	const float ShiftGazePoint;

	// �v���C���[�̃|�C���^��ێ����邽�߂̕ϐ�
	PlayerObject* playerObject;

	//�e�I�u�W�F�N�g�Ƃ̍�
	Vector3 offsetPos;

	//�ړ���position
	Vector3 tmpMovePos;
	Vector3 tmpPosition;

	// �����߂����s������Ɠ��������ʒu��ۑ�����Vector3�ϐ�
	Vector3 hitPosition;

	// �����蔻����s���N���X(AABB/����)
	BoxCollider* boxcollider;

	// view�s��
	Matrix4 view;

	//�Ǐ]��̃I�u�W�F�N�g���������Ă��邩
	bool hasParentObject;

	// �����߂����s������Ɠ����������𔻒肷��t���O
	bool hitFlag;

	// �O�̃t���[���ŉ����߂����s������Ɠ����������𔻒肷��t���O
	bool tmpHitFlag;

	//�J�����̍���
	float height;

	//�J������]�v�Z�p�̃��[�ƃs�b�`
	float yaw;
	float pitch;

	//�J������]�̔��a
	float radius;





};

