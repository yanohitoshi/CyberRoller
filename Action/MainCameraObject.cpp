//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "MainCameraObject.h"
#include "CameraObjectBase.h"
#include "Renderer.h"
#include "ColliderComponent.h"
#include "InputSystem.h"
#include "PlayerObject.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "FirstStageScene.h"
#include "FirstStageUI.h"
#include "CountDownFont.h"
#include "PlayerObjectStateIdlingDance.h"

/*
@brief	�R���X�g���N�^
@param	�|�W�V����
@param	�v���C���[�̃|�C���^
*/
MainCameraObject::MainCameraObject(const Vector3 _pos, PlayerObject* _playerObject) 
	: CameraObjectBase(false,Tag::CAMERA)
	, YawSpeed(0.055f)
	, PitchSpeed(0.03f)
	, MaxPitch(70.0f)
	, MinPitch(-30.0f)
	, MaxRadius(700.0f)
	, MinRadius(10.0f)
	, DanceRadius(500.0f)
	, TimeOverRadius(400.0f)
	, MediumRadius(300.0f)
	, DeltaCorrection(8.0f)
	, AutomaticMoveSpeed(0.01f)
	, ShiftGazePoint(100.0f)
	, CorrectionBackRadius(20.f)
	, AabbInitMax(Vector3(100.0f, 100.0f, 50.0f))
	, AabbInitMin(Vector3(-100.0f, -100.0f, -50.0f))
{
	// �����o�[�ϐ��̏�����
	SetPosition(_pos);
	yaw = Math::ToRadians(180);
	pitch = Math::ToRadians(30);
	radius = MaxRadius;
	height = 0.0f;
	forwardVec = Vector3::UnitX;
	tmpMovePos = Vector3::Zero;
	lerpObjectPos = Vector3::Zero;
	hitPosition = Vector3::Zero;
	hitFlag = false;
	tmpHitFlag = false;

	//�����蔻��p�̃R���|�[�l���g�̒ǉ��Ə�����
	boxcollider = new BoxCollider(this, PhysicsTag::CAMERA_TAG, GetOnCollisionFunc());
	AABB aabb = { AabbInitMin,AabbInitMax };
	boxcollider->SetObjectBox(aabb);

	// �v���C���[�̃|�C���^��ۑ�
	playerObject = _playerObject;

}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
MainCameraObject::~MainCameraObject()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void MainCameraObject::UpdateGameObject(float _deltaTime)
{
	// �v���C���[���N���A��ԂłȂ����^�C���I�[�o�[�ł��Ȃ��x���Ă����Ȃ�������
	if (playerObject->GetClearFlag() == false && CountDownFont::GetTimeOverFlag() == false && !PlayerObjectStateIdlingDance::GetIsDancing())
	{
		// �Q�[���v���C���̈ړ��v�Z����
		InGameMovableProcess(_deltaTime);
	}
	else if (playerObject->GetClearFlag() == true) // �ŏI�X�e�[�W���N���A���Ă�����
	{
		// �N���A��Ԃ̏���
		GameClearProcess(_deltaTime);
	}
	else if (CountDownFont::GetTimeOverFlag() == true) // �^�C���I�[�o�[�ɂȂ�����
	{
		// �Q�[���I�[�o�[���̏���
		GameOverProcess(_deltaTime);
	}
	else if (PlayerObjectStateIdlingDance::GetIsDancing() && CountDownFont::GetTimeOverFlag() == false)
	{
		// ��莞�ԓ��͂��Ȃ��v���C���[���x���Ă��鎞�̏���
		PlayerInDanceProcess(_deltaTime);
	}

}

/*
@fn ���͂������Ŏ󂯎��X�V�֐�
@brief ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
@param	_keyState ���͏��
*/
void MainCameraObject::GameObjectInput(const InputState& _keyState)
{
	// ���͏�ԃ`�F�b�N�֐�
	ChackInputProcess(_keyState);

	// �s�b�`�␳�֐�
	CorrectionPitch();
}

/*
@param _offset�@���������W�Ƃ̍�
@param _parentPos�@������W
*/
void MainCameraObject::SetViewMatrixLerpObject(const Vector3 & _offset, const Vector3 & _parentPos)
{
	hasParentObject = true;
	offsetPos = _offset;
	lerpObjectPos = _parentPos;
}

/*
@brief �Q�[�����̈ړ�����
@param	_deltaTime �O�̃t���[���ł�����������
*/
void MainCameraObject::InGameMovableProcess(float _deltaTime)
{
	// �J�������a�̕␳�֐�
	CorrectionRadius();

	// �|�W�V�����v�Z�֐�
	CalculationPosition(_deltaTime);

	// �r���[�s��v�Z�֐�
	CalculationViewMatrix();

	// �v���C���[���ɓn���O���x�N�g���𐶐�
	forwardVec = lerpObjectPos - position;
	// ���K��
	forwardVec.Normalize();
	// Z�����Œ�
	forwardVec.z = 0.0f;

	// �����蔻����s���I�u�W�F�N�g�Ɠ��������|�W�V������ۑ�
	tmpHitFlag = hitFlag;

	// �����蔻����s���ۂɗ��p����ϐ��̏�����
	hitPosition = Vector3::Zero;
	hitFlag = false;
}

/*
@brief ���a�␳�v�Z����
*/
void MainCameraObject::CorrectionRadius()
{
	// ���̃t���[���œ������Ă��đO�̃t���[���œ������Ă��Ȃ����
	if (hitFlag == true && tmpHitFlag == false)
	{
		// ���������|�W�V����x���}�C�i�X��������
		if (hitPosition.x < 0.0f)
		{
			hitPosition.x *= -1.0f;
		}

		// ���������|�W�V����y���}�C�i�X��������
		if (hitPosition.y < 0.0f)
		{
			hitPosition.y *= -1.0f;
		}

		// ���������|�W�V�������׏����������J�����̉�]���a�Ƃ��č̗p
		if (hitPosition.x < hitPosition.y)
		{
			// ����Ώە����瓖�������ꏊ�������Ē��������
			radius = lerpObjectPos.x - hitPosition.x;
			// ���̂܂܎g���ƕǂɂ߂荞�މ\��������̂ŏ�������������
			radius -= CorrectionBackRadius;
		}
		else if (hitPosition.x > hitPosition.y)
		{
			// ����Ώە����瓖�������ꏊ�������Ē��������
			radius = lerpObjectPos.y - hitPosition.y;
			// ���̂܂܎g���ƕǂɂ߂荞�މ\��������̂ŏ�������������
			radius -= CorrectionBackRadius;
		}

		// ���a���}�C�i�X�ɂȂ��Ă�����v���X�ɕϊ�
		if (radius <= 0.0f)
		{
			radius *= -1.0f;
		}
	}
	else
	{
		// ���a��萔��
		radius = MaxRadius;
	}

	// ���a���ő�l�𒴂��Ă�����
	if (radius >= MaxRadius)
	{
		// �ő�l����
		radius = MaxRadius;
	}
	else if (radius <= MinRadius) // ���a���ŏ��l��������Ă����炢����
	{
		// �ŏ��l����
		radius = MinRadius;
	}

	// �J�����̍�����0.0f�ȉ��ł��ŏ��l��荂��������
	if (pitch < 0.0f && pitch > MinPitch)
	{
		// ���a�����������ĒǐՂ���I�u�W�F�N�g�ɋ߂Â���
		radius -= MediumRadius;
	}
}

/*
@brief �s�b�`�␳�v�Z����
*/
void MainCameraObject::CorrectionPitch()
{
	// �s�b�`���ő�l�𒴂��Ă�����
	if (pitch > Math::ToRadians(MaxPitch))
	{
		// �ő�l����
		pitch = Math::ToRadians(MaxPitch);
	}
	// �s�b�`���ŏ��l��������Ă�����
	if (pitch < Math::ToRadians(MinPitch))
	{
		// �ŏ��l����
		pitch = Math::ToRadians(MinPitch);
	}
}

/*
@brief �|�W�V�����v�Z����
@param	_deltaTime �O�̃t���[���ł�����������
*/
void MainCameraObject::CalculationPosition(float _deltaTime)
{
	// ��]�p�Ɣ��a��p���ĉ��̃|�W�V������ݒ�
	tmpMovePos.x = radius * cosf(pitch) * cosf(yaw) + lerpObjectPos.x;
	tmpMovePos.y = radius * cosf(pitch) * sinf(yaw) + lerpObjectPos.y;
	tmpMovePos.z = radius * sinf(pitch) + height + lerpObjectPos.z;

	// ���̃|�W�V�����ƌ��݂̃|�W�V�����Ő��`���
	position = Vector3::Lerp(position, tmpMovePos, _deltaTime * DeltaCorrection);

	// ���`��Ԃ����|�W�V�������Z�b�g
	SetPosition(position);
}

/*
@brief �r���[�s��v�Z����
*/
void MainCameraObject::CalculationViewMatrix()
{
	// �Ǐ]����I�u�W�F�N�g�̃|�W�V��������
	Vector3 viewPosition = Vector3(lerpObjectPos.x, lerpObjectPos.y, lerpObjectPos.z + ShiftGazePoint);
	// �X�V�����|�W�V�����ƒǏ]����I�u�W�F�N�g�̃|�W�V������p����view�s����X�V
	view = Matrix4::CreateLookAt(position, viewPosition, Vector3::UnitZ);
	// �X�V����view�s����Z�b�g
	RENDERER->SetViewMatrix(view);
}

/*
@brief �Q�[���N���A���̏���
@param	_deltaTime �O�̃t���[���ł�����������
*/
void MainCameraObject::GameClearProcess(float _deltaTime)
{
	// �����悪�N���A�p�I�u�W�F�N�g�ɕς���Ă���̂ł��̃|�W�V������p����view�s����X�V
	view = Matrix4::CreateLookAt(position, lerpObjectPos, Vector3::UnitZ);
	// view�s����Z�b�g
	RENDERER->SetViewMatrix(view);
}

/*
@brief �Q�[���I�[�o�[���̏���
@param	_deltaTime �O�̃t���[���ł�����������
*/
void MainCameraObject::GameOverProcess(float _deltaTime)
{
	// ��]�p�������X�V
	yaw += AutomaticMoveSpeed;

	// �|�W�V�����̍X�V���^�C���I�[�o�[�p�̔��a�ōs��
	tmpMovePos.x = TimeOverRadius * cosf(pitch) * cosf(yaw) + lerpObjectPos.x;
	tmpMovePos.y = TimeOverRadius * cosf(pitch) * sinf(yaw) + lerpObjectPos.y;
	tmpMovePos.z = radius * sinf(pitch) + height + lerpObjectPos.z;

	// ���̃|�W�V�����ƌ��݂̃|�W�V�����Ő��`���
	position = Vector3::Lerp(position, tmpMovePos, _deltaTime * DeltaCorrection);
	// ���`��Ԃ����|�W�V�������Z�b�g
	SetPosition(position);

	// �X�V�����|�W�V�����ƒǏ]����I�u�W�F�N�g�̃|�W�V������p����view�s����X�V
	view = Matrix4::CreateLookAt(position, lerpObjectPos, Vector3::UnitZ);
	// �X�V����view�s����Z�b�g
	RENDERER->SetViewMatrix(view);
}

/*
@brief �v���C���[���_���X��Ԃ̎��̏���
@param	_deltaTime �O�̃t���[���ł�����������
*/
void MainCameraObject::PlayerInDanceProcess(float _deltaTime)
{
	// ��]�p�������X�V
	yaw += AutomaticMoveSpeed;

	// �|�W�V�����̍X�V���v���C���[���x���Ă��鎞�p�̔��a�ōs��
	tmpMovePos.x = DanceRadius * cosf(pitch) * cosf(yaw) + lerpObjectPos.x;
	tmpMovePos.y = DanceRadius * cosf(pitch) * sinf(yaw) + lerpObjectPos.y;
	tmpMovePos.z = radius * sinf(pitch) + height + lerpObjectPos.z;

	// ���̃|�W�V�����ƌ��݂̃|�W�V�����Ő��`���
	position = Vector3::Lerp(position, tmpMovePos, _deltaTime * DeltaCorrection);
	// ���`��Ԃ����|�W�V�������Z�b�g
	SetPosition(position);

	// �X�V�����|�W�V�����ƒǏ]����I�u�W�F�N�g�̃|�W�V������p����view�s����X�V
	view = Matrix4::CreateLookAt(position, lerpObjectPos, Vector3::UnitZ);
	// �X�V����view�s����Z�b�g
	RENDERER->SetViewMatrix(view);

}

/*
@brief ���̓`�F�b�N�Ƃ��̏���
@param	_keyState ���͏��
*/
void MainCameraObject::ChackInputProcess(const InputState& _keyState)
{

	// �N���A��Ԃ��ᖳ��������
	if (playerObject->GetClearFlag() == false)
	{
		// �E�X�e�B�b�N�̊p�x��ۑ�����x�N�g���ϐ�
		Vector2 rightAxis = Vector2(0.0f, 0.0f);
		rightAxis = _keyState.Controller.GetLAxisRightVec();

		// �L�[�{�[�h���͂ƉE�X�e�B�b�N��X���̊p�x�����đ��x����ǉ�
		if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_RIGHT) == 1 ||
			rightAxis.x > 0.0f)
		{
			yaw += YawSpeed;
		}
		if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_LEFT) == 1 ||
			rightAxis.x < 0.0f)
		{
			yaw -= YawSpeed;
		}
		// �L�[�{�[�h���͂ƉE�X�e�B�b�N��Y���̊p�x�����đ��x����ǉ�
		if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_UP) == 1 ||
			rightAxis.y < 0.0f)
		{
			pitch -= PitchSpeed;
		}
		if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_DOWN) == 1 ||
			rightAxis.y > 0.0f)
		{
			pitch += PitchSpeed;
		}

	}

}

/*
@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
@param	��������GameObject
@param	��������GameObject�̓����蔻��^�O
*/
void MainCameraObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{	
	// �q�b�g�����ۂɃq�b�g�t���O��false��������
	if (hitFlag == false)
	{
		// �q�b�g�t���O��true��
		hitFlag = true;
		// ���������I�u�W�F�N�g�̃|�W�V������ۑ� 
		hitPosition = _hitObject.GetPosition();
	}

	// �����߂��p�Ƀ��[���hBox��ۑ�
	AABB myAabb = boxcollider->GetWorldBox();

	if (_hitObject.GetisPushBackToCamera())
	{
		// �����߂��֐����Ăяo��
		FixCollision(myAabb, _hitObject.GetAabb());
	}

}

/*
@brief �����߂����s��
@param ������AABB
@param �����AABB
@param �y�A�ƂȂ鑊���Tag
*/
void MainCameraObject::FixCollision(AABB& myAABB, const AABB& pairAABB)
{
	// ���x�␳�x�N�g���ϐ�
	Vector3 ment = Vector3::Zero;
	// �����߂��v�Z
	CalcCollisionFixVec(myAABB, pairAABB, ment);
	// �|�W�V�������X�V
	SetPosition(position + ment);
}

/*
@brief �����߂��v�Z���s��
@param ������AABB
@param �����AABB
@param �����߂���
*/
void MainCameraObject::CalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec)
{
	_calcFixVec = Vector3::Zero;

	float dx1 = _fixedBox.min.x - _movableBox.max.x;
	float dx2 = _fixedBox.max.x - _movableBox.min.x;
	float dy1 = _fixedBox.min.y - _movableBox.max.y;
	float dy2 = _fixedBox.max.y - _movableBox.min.y;
	float dz1 = _fixedBox.min.z - _movableBox.max.z;
	float dz2 = _fixedBox.max.z - _movableBox.min.z;

	// dx, dy, dz �ɂ� ���ꂼ��1,2�̂�����Βl�������������Z�b�g����
	float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
	float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;
	float dz = (Math::Abs(dz1) < Math::Abs(dz2)) ? dz1 : dz2;


	// x, y, z�̂����ł��������������ňʒu�𒲐�
	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		_calcFixVec.x = dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		_calcFixVec.y = dy;
	}
	else
	{
		_calcFixVec.z = dz;
	}

}