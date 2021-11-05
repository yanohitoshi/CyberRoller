#include "CameraObjectStateSceneClear.h"
#include "Renderer.h"
#include "PlayerObject.h"

CameraState CameraObjectStateSceneClear::Update(CameraObjectBase* _owner, float _deltaTime)
{
	// ��]�p�������X�V
	yaw += AutomaticMoveSpeed;

	Vector3 tmpMovePos;
	Vector3 lerpObjectPos;
	// �Ǐ]����I�u�W�F�N�g�̃|�W�V�������擾
	lerpObjectPos = _owner->GetLerpObjectPos();
	// �|�W�V�����̍X�V���v���C���[���x���Ă��鎞�p�̔��a�ōs��
	tmpMovePos.x = GameClearRadius * cosf(yaw) + lerpObjectPos.x;
	tmpMovePos.y = GameClearRadius * sinf(yaw) + lerpObjectPos.y;

	++trackingCount;
	if (trackingCount <=TrackingTime)
	{
		tmpMovePos.z = lerpObjectPos.z - 400.0f;
		stopPisitionZ = tmpMovePos.z;
	}
	else
	{
		tmpMovePos.z = stopPisitionZ;
	}

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

	return state;
}

void CameraObjectStateSceneClear::Enter(CameraObjectBase* _owner, float _deltaTime)
{
	state = CameraState::SCENECLEAR;
	yaw = 0.0f;
	trackingCount = 0;
	stopPisitionZ = 0.0f;
}