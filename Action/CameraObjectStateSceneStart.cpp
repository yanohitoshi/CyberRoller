#include "CameraObjectStateSceneStart.h"
#include "Renderer.h"
#include "PlayerObject.h"

CameraState CameraObjectStateSceneStart::Update(CameraObjectBase* _owner, float _deltaTime)
{
	Vector3 tmpMovePos;
	Vector3 lerpObjectPos;
	GameObject* lerpObject = _owner->GetLerpObject();
	// �Ǐ]����I�u�W�F�N�g�̃|�W�V�������擾
	lerpObjectPos = lerpObject->GetPosition();

	Vector3 setPosition;
	// ���̃|�W�V�����ƌ��݂̃|�W�V�����Ő��`���
	setPosition = Vector3::Lerp(_owner->GetPosition(), tmpMovePos, _deltaTime);

	// ���`��Ԃ����|�W�V�������Z�b�g
	_owner->SetPosition(setPosition);

	Matrix4 view;
	// �����悪�N���A�p�I�u�W�F�N�g�ɕς���Ă���̂ł��̃|�W�V������p����view�s����X�V
	view = Matrix4::CreateLookAt(_owner->GetPosition(), lerpObjectPos, Vector3::UnitZ);
	// view�s����Z�b�g
	RENDERER->SetViewMatrix(view);

	return state;
}

void CameraObjectStateSceneStart::Enter(CameraObjectBase* _owner, float _deltaTime)
{
	state = CameraState::SCENESTART;
}