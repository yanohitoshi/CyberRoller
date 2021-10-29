#include "CameraObjectStateLandscape.h"
#include "Renderer.h"
#include "PlayerObject.h"

CameraState CameraObjectStateLandscape::Update(CameraObjectBase* _owner, float _deltaTime)
{
	Vector3 tmpMovePos;
	Vector3 lerpObjectPos;
	GameObject* lerpObject = _owner->GetLerpObject();

	// �Ǐ]����I�u�W�F�N�g�̃|�W�V�������擾
	lerpObjectPos = lerpObject->GetPosition();
	// ���̈ړ��|�W�V�����ϐ��ɑ��
	tmpMovePos = lerpObjectPos;
	tmpMovePos.z += offsetPosition.z;
	tmpMovePos.y += offsetPosition.y;

	Vector3 setPosition;
	// ���̃|�W�V�����ƌ��݂̃|�W�V�����Ő��`���
	setPosition = Vector3::Lerp(_owner->GetPosition(), tmpMovePos, _deltaTime * DeltaCorrection);

	// ���`��Ԃ����|�W�V�������Z�b�g
	_owner->SetPosition(setPosition);

	Matrix4 view;
	// �����悪�N���A�p�I�u�W�F�N�g�ɕς���Ă���̂ł��̃|�W�V������p����view�s����X�V
	view = Matrix4::CreateLookAt(_owner->GetPosition(), lerpObjectPos, Vector3::UnitZ);
	// view�s����Z�b�g
	RENDERER->SetViewMatrix(view);

	Vector3 nextForwardVec;
	// �v���C���[���ɓn���O���x�N�g���𐶐�
	nextForwardVec = lerpObjectPos - _owner->GetPosition();
	// ���K��
	nextForwardVec.Normalize();
	// Z�����Œ�
	nextForwardVec.z = 0.0f;

	_owner->SetCameraVec(nextForwardVec);

	return state;
}

void CameraObjectStateLandscape::Input(CameraObjectBase* _owner, const InputState& _keyState)
{
}

void CameraObjectStateLandscape::Enter(CameraObjectBase* _owner, float _deltaTime)
{
	state = CameraState::LANDSCAPE;
	offsetPosition = _owner->GetOffsetPosition();
}