//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitleCameraObject.h"
#include "Renderer.h"

TitleCameraObject::TitleCameraObject(const Vector3 _pos)
	:CameraObjectBase(false, Tag::TITLE_OBJECT)
	, ShiftGazePoint(800.0f)
	, ShiftPosition(300.0f)
{
	//Title�p�ɕ\�����Ă�object���班�����ꂽ�ʒu�ɔz�u
	SetPosition(Vector3(_pos.x - ShiftPosition, _pos.y, _pos.z + ShiftPosition));
	//Title�p�̃}�b�v�N���G�C�^�[���璆�S�ɂȂ�I�u�W�F�N�g�̈ʒu���J�����̃^�[�Q�b�g�ɕۑ�
	target = _pos;
	target.x = target.x + ShiftGazePoint;	//����ʒu�̔�����
}

TitleCameraObject::~TitleCameraObject()
{
}

void TitleCameraObject::UpdateGameObject(float _deltaTime)
{
	//view�s��𐶐�
	view = Matrix4::CreateLookAt(position, Vector3(target), Vector3::UnitZ);
	//�����_���[��view�s��ɃZ�b�g
	RENDERER->SetViewMatrix(view);
}

void TitleCameraObject::GameObjectInput(const InputState& _keyState)
{
}
