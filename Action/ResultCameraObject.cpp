//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ResultCameraObject.h"
#include "Renderer.h"

/*
@brief	�R���X�g���N�^
@param	�J�����̒����_
*/
ResultCameraObject::ResultCameraObject(const Vector3 _pos)
	:CameraObjectBase(false, Tag::RESULT_OBJECT)
	, ShiftPosition(5000.0f)
{
	//Title�p�ɕ\�����Ă�object���班�����ꂽ�ʒu�ɔz�u
	SetPosition(Vector3(_pos.x - ShiftPosition, _pos.y , _pos.z));
	// ���U���g�V�[���ł̃J�����̒����_��ۑ�
	target = _pos;
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
ResultCameraObject::~ResultCameraObject()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	deltaTime�Œ�
*/
void ResultCameraObject::UpdateGameObject(float _deltaTime)
{
	//view�s��𐶐�
	view = Matrix4::CreateLookAt(position, target, Vector3::UnitZ);
	//�����_���[��view�s��ɃZ�b�g
	RENDERER->SetViewMatrix(view);
}