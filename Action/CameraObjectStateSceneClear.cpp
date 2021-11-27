//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CameraObjectStateSceneClear.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return CameraState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
*/
CameraState CameraObjectStateSceneClear::Update(CameraObjectBase* _owner, float _deltaTime)
{
	// ��]�p�������X�V
	yaw += AutomaticMoveSpeed;

	// ���̈ړ���|�W�V����
	Vector3 tmpMovePos;
	// �Ǐ]����I�u�W�F�N�g�̃|�W�V����
	Vector3 lerpObjectPos;
	// �Ǐ]����I�u�W�F�N�g�̃|�W�V�������擾
	lerpObjectPos = _owner->GetLerpObjectPos();
	// �|�W�V�����̍X�V���v���C���[���x���Ă��鎞�p�̔��a�ōs��
	tmpMovePos.x = GameClearRadius * cosf(yaw) + lerpObjectPos.x;
	tmpMovePos.y = GameClearRadius * sinf(yaw) + lerpObjectPos.y;

	// �ǐՂ��鎞�Ԃ��J�E���g
	++trackingCount;

	// �ǐՎ��ԓ���������
	if (trackingCount <=TrackingTime)
	{
		// �ǐՂ���
		tmpMovePos.z = lerpObjectPos.z - OffsetZ;
		stopPisitionZ = tmpMovePos.z;
	}
	else
	{
		// ���̏�Œ�~
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
	RENDERING_OBJECT_MANAGER->SetViewMatrix(view);

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void CameraObjectStateSceneClear::Enter(CameraObjectBase* _owner, float _deltaTime)
{
	// �X�e�[�^�X���V�[���N���A��ԂɕύX
	state = CameraState::SCENECLEAR;
	// �ϐ�������
	yaw = InitYaw;
	trackingCount = 0;
	stopPisitionZ = 0.0f;
}