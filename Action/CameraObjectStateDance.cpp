#include "CameraObjectStateDance.h"
#include "Renderer.h"
#include "PlayerObject.h"

CameraState CameraObjectStateDance::Update(CameraObjectBase* _owner, float _deltaTime)
{
	// ��]�p�������X�V
	yaw += AutomaticMoveSpeed;

	Vector3 tmpMovePos;
	Vector3 lerpObjectPos;
	GameObject* lerpObject = _owner->GetLerpObject();
	// �Ǐ]����I�u�W�F�N�g�̃|�W�V�������擾
	lerpObjectPos = lerpObject->GetPosition();
	// �|�W�V�����̍X�V���v���C���[���x���Ă��鎞�p�̔��a�ōs��
	tmpMovePos.x = DanceRadius * cosf(yaw) + lerpObjectPos.x;
	tmpMovePos.y = DanceRadius * sinf(yaw) + lerpObjectPos.y;
	tmpMovePos.z = lerpObjectPos.z + 600.0f;

	Vector3 setPosition;
	// ���̃|�W�V�����ƌ��݂̃|�W�V�����Ő��`���
	setPosition = Vector3::Lerp(_owner->GetPosition(), tmpMovePos, _deltaTime * DeltaCorrection);

	// ���`��Ԃ����|�W�V�������Z�b�g
	_owner->SetPosition(setPosition);

	Matrix4 view;
	// �X�V�����|�W�V�����ƒǏ]����I�u�W�F�N�g�̃|�W�V������p����view�s����X�V
	view = Matrix4::CreateLookAt(_owner->GetPosition(), lerpObjectPos, Vector3::UnitZ);
	// �X�V����view�s����Z�b�g
	RENDERER->SetViewMatrix(view);

	if (!_owner->GetLerpObject()->GetIsDancing())
	{
		state = CameraState::NORMAL;
	}

	return state;
}

void CameraObjectStateDance::Enter(CameraObjectBase* _owner, float _deltaTime)
{
	state = CameraState::DANCE;
	yaw = 180.0f;
}
