#include "CameraObjectStateGameOver.h"
#include "Renderer.h"
#include "PlayerObject.h"

CameraState CameraObjectStateGameOver::Update(CameraObjectBase* _owner, float _deltaTime)
{
	// ��]�p�������X�V
	yaw += AutomaticMoveSpeed;

	Vector3 tmpMovePos;
	Vector3 lerpObjectPos;
	GameObject* lerpObject = _owner->GetLerpObject();
	// �Ǐ]����I�u�W�F�N�g�̃|�W�V�������擾
	lerpObjectPos = lerpObject->GetPosition();
	// �|�W�V�����̍X�V���v���C���[���x���Ă��鎞�p�̔��a�ōs��
	tmpMovePos.x = GameOverRadius * cosf(yaw) + lerpObjectPos.x;
	tmpMovePos.y = GameOverRadius * sinf(yaw) + lerpObjectPos.y;
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

	return state;
}

void CameraObjectStateGameOver::Input(CameraObjectBase* _owner, const InputState& _keyState)
{
}

void CameraObjectStateGameOver::Enter(CameraObjectBase* _owner, float _deltaTime)
{
	state = CameraState::GAMEOVER;
	yaw = 180.0f;
}
