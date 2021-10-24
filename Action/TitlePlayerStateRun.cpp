#include "TitlePlayerStateRun.h"
#include "TitlePlayerObject.h"
#include "SkeletalMeshComponent.h"

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return TitlePlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
*/
TitlePlayerState TitlePlayerStateRun::Update(TitlePlayerObject* _owner, float _deltaTime)
{
	// �����|�W�V�����ɖ߂��Ă��Ă��邩����
	if (_owner->GetPosition().y >= initPosition.y + CorrectionValuePositionY)
	{
		// �߂��Ă��Ă��Ȃ���������`�⊮�����Ȃ���ړ��p��
		// ���|�W�V�����ϐ�
		Vector3 tmpPosition;
		// ���`�⊮���Ƃ�ϐ��ɕۑ�
		tmpPosition = Vector3::Lerp(_owner->GetPosition(), initPosition, _deltaTime);
		// �|�W�V�������Z�b�g
		_owner->SetPosition(tmpPosition);
	}
	else
	{
		// �߂��Ă��Ă�����W�����v�\��Ԃ�
		isAvailableJump = true;
	}
	
	JumpDelayProcess(_owner);

	// �W�����v�t���O�𔻒�
	if (_owner->GetJumpFlag())
	{
		_owner->SetJumpCount(jumpCount);
		state = TitlePlayerState::JUMP_START;
	}

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void TitlePlayerStateRun::Enter(TitlePlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(TitlePlayerState::RUN));
	// state��DEAD��Ԃɂ��ĕۑ�
	state = TitlePlayerState::RUN;

	// ������
	jumpDelayCount = 0;
	isAvailableJump = false;
	jumpCount = _owner->GetJumpCount();
	initPosition = _owner->GetInitPosition();
}

/*
@fn �W�����v�f�B���C�����֐�
@param	_owner �e�N���X�̃|�C���^
*/
void TitlePlayerStateRun::JumpDelayProcess(TitlePlayerObject* _owner)
{
	// �W�����v����Ԋu�𐔂���
	++jumpDelayCount;

	// ���Ԃ�������W�����v�����W�����v�J�n�A�j���[�V�������Đ�
	if (jumpDelayCount >= JumpDelayTime && isAvailableJump)
	{
		// �W�����v�t���O��true��
		_owner->SetJumpFlag(true);
		++jumpCount;
	}
}