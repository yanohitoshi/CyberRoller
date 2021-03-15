#pragma once
#include "GameObject.h"
#include "CameraObjectBase.h"
#include "PlayerObject.h"


class LineSegmentCollider;
class SphereCollider;
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
	MainCameraObject(const Vector3 _pos);

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
	void FixCollision(AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag);

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
	@brief ���X�|�[�������Ƃ��ɃJ�����̈ʒu��������ԂɃZ�b�g����֐�
	*/
	void ReSetYaw() { yaw = Math::ToRadians(180); }

private:

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	//�e�I�u�W�F�N�g�Ƃ̍�
	Vector3 offsetPos;
	//�Ǐ]��̃I�u�W�F�N�g���W
	Vector3 lerpObjectPos;
	//�Ǐ]��̃I�u�W�F�N�g���������Ă��邩
	bool hasParentObject;
	Vector3 cameraFront = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 cameraUp = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 direction;
	Vector3 vel;
	//�J�����̍���
	float height;
	//�J������]�v�Z�p�̃��[�ƃs�b�`
	float yaw;
	float pitch;
	//�J�����̈ړ����x
	static const float yawSpeed;
	static const float pitchSpeed;

	//�J������]�̔��a
	float r;

	//�ړ���position
	Vector3 tmpMovePos;
	Vector3 tmpPosition;

	// �����蔻����s���N���X(AABB/����/���́�����������)
	BoxCollider* boxcollider;
	LineSegmentCollider* lineSegmentCollider;
	SphereCollider* sphereCollider;

	// view�s��
	Matrix4 view;

};

