#include "AutoMoveCamera.h"
#include "Renderer.h"
#include "ColliderComponent.h"
#include "InputSystem.h"
#include "PlayerObject.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "CountDownFont.h"
#include "PlayerObjectStateIdlingDance.h"

AutoMoveCamera::AutoMoveCamera(const Vector3 _pos, PlayerObject* _playerObject)
	: CameraObjectBase(false, Tag::CAMERA)
{
	// �����o�[�ϐ��̏�����
	SetPosition(_pos);

	forwardVec = Vector3::UnitX;
	tmpMovePos = Vector3::Zero;
	lerpObjectPos = Vector3::Zero;
	// �v���C���[�̃|�C���^��ۑ�
	playerObject = _playerObject;
	cameraMode = CameraMode::NORMAL;
}

AutoMoveCamera::~AutoMoveCamera()
{
}

void AutoMoveCamera::UpdateGameObject(float _deltaTime)
{

	if (cameraMode == CameraMode::BEHIND)
	{
		Behind(_deltaTime);
	}
	else
	{
		InAction(_deltaTime);
	}

	// �v���C���[���ɓn���O���x�N�g���𐶐�
	forwardVec = lerpObjectPos - position;
	// ���K��
	forwardVec.Normalize();
	// Z�����Œ�
	forwardVec.z = 0.0f;

	cameraMode = CameraMode::NORMAL;
}

void AutoMoveCamera::GameObjectInput(const InputState& _keyState)
{
}

void AutoMoveCamera::InAction(float _deltaTime)
{
	// �Ǐ]����I�u�W�F�N�g�̃|�W�V�������擾
	lerpObjectPos = playerObject->GetPosition();
	// ���̈ړ��|�W�V�����ϐ��ɑ��
	tmpMovePos = lerpObjectPos;
	tmpMovePos.x -= 600.0f;
	tmpMovePos.z += 600.0f;
	tmpMovePos.y += 700.0f;
	// ���̃|�W�V�����ƌ��݂̃|�W�V�����Ő��`���
	position = Vector3::Lerp(position, tmpMovePos, _deltaTime * DeltaCorrection);

	// ���`��Ԃ����|�W�V�������Z�b�g
	SetPosition(position);
	Vector3 tmpViewPos = lerpObjectPos;
	//tmpViewPos.x += 200.0f;
	// �����悪�N���A�p�I�u�W�F�N�g�ɕς���Ă���̂ł��̃|�W�V������p����view�s����X�V
	view = Matrix4::CreateLookAt(position, tmpViewPos, Vector3::UnitZ);
	// view�s����Z�b�g
	RENDERER->SetViewMatrix(view);
}

void AutoMoveCamera::Behind(float _deltaTime)
{
	// �Ǐ]����I�u�W�F�N�g�̃|�W�V�������擾
	lerpObjectPos = playerObject->GetPosition();
	// ���̈ړ��|�W�V�����ϐ��ɑ��
	tmpMovePos = lerpObjectPos;
	tmpMovePos.x -= 600.0f;
	tmpMovePos.z += 600.0f;
	//tmpMovePos.y += 700.0f;
	// ���̃|�W�V�����ƌ��݂̃|�W�V�����Ő��`���
	position = Vector3::Lerp(position, tmpMovePos, _deltaTime * DeltaCorrection);

	// ���`��Ԃ����|�W�V�������Z�b�g
	SetPosition(position);
	Vector3 tmpViewPos = lerpObjectPos;
	//tmpViewPos.x += 200.0f;
	// �����悪�N���A�p�I�u�W�F�N�g�ɕς���Ă���̂ł��̃|�W�V������p����view�s����X�V
	view = Matrix4::CreateLookAt(position, tmpViewPos, Vector3::UnitZ);
	// view�s����Z�b�g
	RENDERER->SetViewMatrix(view);
}
