#include "TitlePlayerStateJumpStart.h"
#include "TitlePlayerObject.h"
#include "SkeletalMeshComponent.h"

TitlePlayerState TitlePlayerStateJumpStart::Update(TitlePlayerObject* _owner, float _deltaTime)
{

	// �d�͂��|����
	velocity.z -= Gravity * _deltaTime;

	// �������x���K��l�𒴂��Ă�����
	if (velocity.z <= MaxFallSpeed)
	{
		// �������x���K��l�ɌŒ肷��
		velocity.z = MaxFallSpeed;
	}

	// �W�����v���̃J�E���g�𐔂���
	++jumpFrameCount;
	// ����ɃW�����v�͂�ǉ�
	jumpPower += JumpSpeed;
	// �W�����v�͂�ǉ�
	velocity.z = jumpPower;

	_owner->SetPosition(_owner->GetPosition() + velocity);

	if (!skeletalMeshComponent->IsPlaying())
	{
		_owner->SetJumpPower(jumpPower);
		_owner->SetJumpFrameCount(jumpFrameCount);
		state = TitlePlayerState::JUMP_LOOP;
	}

	if (!skeletalMeshComponent->IsPlaying() && _owner->GetJumpCount() % 3 == 0)
	{
		_owner->SetJumpCount(0);
		state = TitlePlayerState::JUMP_ATTACK;
	}

    return state;
}

void TitlePlayerStateJumpStart::Enter(TitlePlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(TitlePlayerState::JUMP_START));
	// state��DEAD��Ԃɂ��ĕۑ�
	state = TitlePlayerState::JUMP_START;
	jumpPower = FirstJumpPower;
	jumpFrameCount = 0;
}
