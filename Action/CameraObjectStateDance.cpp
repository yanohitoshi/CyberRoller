#include "CameraObjectStateDance.h"
#include "Renderer.h"
#include "PlayerObject.h"

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return CameraState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
*/
CameraState CameraObjectStateDance::Update(CameraObjectBase* _owner, float _deltaTime)
{
	// ��]�p�������X�V
	yaw += AutomaticMoveSpeed;

	// ���|�W�V����
	Vector3 tmpMovePos;
	// �Ǐ]����I�u�W�F�N�g�̃|�W�V����
	Vector3 lerpObjectPos;
	// �Ǐ]����I�u�W�F�N�g�̃|�C���^
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

	// �r���[�s��
	Matrix4 view;
	// �X�V�����|�W�V�����ƒǏ]����I�u�W�F�N�g�̃|�W�V������p����view�s����X�V
	view = Matrix4::CreateLookAt(_owner->GetPosition(), lerpObjectPos, Vector3::UnitZ);
	// �X�V����view�s����Z�b�g
	RENDERER->SetViewMatrix(view);

	// �ǐՑΏۂ��_���X���łȂ��Ȃ�����
	if (!_owner->GetLerpObject()->GetIsDancing())
	{
		// �ʏ��Ԃ�Ԃ�
		state = CameraState::NORMAL;
	}

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void CameraObjectStateDance::Enter(CameraObjectBase* _owner, float _deltaTime)
{
	// �X�e�[�^�X���_���X��ԂɕύX
	state = CameraState::DANCE;
	// ���[�ϐ�������
	yaw = InitYaw;
}
