//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitleCameraObject.h"
#include "RenderingObjectManager.h"

/*
@brief	�R���X�g���N�^
@param	�|�W�V����
*/
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

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
TitleCameraObject::~TitleCameraObject()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	deltaTime�Œ�
*/
void TitleCameraObject::UpdateGameObject(float _deltaTime)
{
	//view�s��𐶐�
	view = Matrix4::CreateLookAt(position, Vector3(target), Vector3::UnitZ);
	//�����_���[��view�s��ɃZ�b�g
	RENDERING_OBJECT_MANAGER->SetViewMatrix(view);
}