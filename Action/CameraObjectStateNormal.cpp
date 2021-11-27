//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CameraObjectStateNormal.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return CameraState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
*/
CameraState CameraObjectStateNormal::Update(CameraObjectBase* _owner, float _deltaTime)
{
	// ���|�W�V����
	Vector3 tmpMovePos;
	// �Ǐ]����I�u�W�F�N�g�̃|�W�V����
	Vector3 lerpObjectPos;
	// �Ǐ]����I�u�W�F�N�g�̃|�C���^
	GameObject* lerpObject = _owner->GetLerpObject();
	// �Ǐ]����I�u�W�F�N�g�̃|�W�V�������擾
	lerpObjectPos = lerpObject->GetPosition();
	// ���̈ړ��|�W�V�����ϐ��ɑ��
	tmpMovePos = lerpObjectPos;
	tmpMovePos.x += offsetPosition.x;
	tmpMovePos.z += offsetPosition.z;

	Vector3 setPosition;
	// ���̃|�W�V�����ƌ��݂̃|�W�V�����Ő��`���
	setPosition = Vector3::Lerp(_owner->GetPosition(), tmpMovePos, _deltaTime * DeltaCorrection);

	// ���`��Ԃ����|�W�V�������Z�b�g
	_owner->SetPosition(setPosition);

	Matrix4 view;
	// �����悪�N���A�p�I�u�W�F�N�g�ɕς���Ă���̂ł��̃|�W�V������p����view�s����X�V
	view = Matrix4::CreateLookAt(_owner->GetPosition(), lerpObjectPos, Vector3::UnitZ);
	// view�s����Z�b�g
	RENDERING_OBJECT_MANAGER->SetViewMatrix(view);

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

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void CameraObjectStateNormal::Enter(CameraObjectBase* _owner, float _deltaTime)
{
	// �X�e�[�^�X��ʏ��ԂɕύX
	state = CameraState::NORMAL;
	// �Ǐ]����I�u�W�F�N�g�Ƃ̊Ԋu���擾
	offsetPosition = _owner->GetOffsetPosition();
}
