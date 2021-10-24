#include "TitlePlayerStateJumpStart.h"
#include "TitlePlayerObject.h"
#include "SkeletalMeshComponent.h"

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return TitlePlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
*/
TitlePlayerState TitlePlayerStateJumpStart::Update(TitlePlayerObject* _owner, float _deltaTime)
{
	// �W�����v���̃J�E���g�𐔂���
	++jumpFrameCount;
	// ����ɃW�����v�͂�ǉ�
	jumpPower += JumpSpeed;
	// �d�͂��|����
	jumpPower -= Gravity * _deltaTime;

	// �W�����v�͂�ǉ�
	velocity.z = jumpPower;

	// �������x���K��l�𒴂��Ă�����
	if (velocity.z <= MaxFallSpeed)
	{
		// �������x���K��l�ɌŒ肷��
		velocity.z = MaxFallSpeed;
	}

	// �|�W�V�������X�V
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// animation���I�����Ă�����
	if (!skeletalMeshComponent->IsPlaying())
	{
		// �W�����v�����񐔂����Z
		++jumpCount;
		// �e�N���X�ɒl���Z�b�g
		_owner->SetJumpCount(jumpCount);
		_owner->SetJumpPower(jumpPower);
		_owner->SetJumpFrameCount(jumpFrameCount);
		// �X�e�[�^�X���W�����v���[�v�ɕύX
		state = TitlePlayerState::JUMP_LOOP;
	}

    return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void TitlePlayerStateJumpStart::Enter(TitlePlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(TitlePlayerState::JUMP_START));
	// state��DEAD��Ԃɂ��ĕۑ�
	state = TitlePlayerState::JUMP_START;
	// ������
	jumpPower = FirstJumpPower;
	jumpFrameCount = 0;
	jumpCount = _owner->GetJumpCount();
}