#include "TitlePlayerStateRun.h"
#include "TitlePlayerObject.h"
#include "SkeletalMeshComponent.h"

TitlePlayerState TitlePlayerStateRun::Update(TitlePlayerObject* _owner, float _deltaTime)
{

	JumpDelayProcess(_owner);

	if (_owner->GetJumpFlag())
	{
		_owner->SetJumpCount(jumpCount);
		state = TitlePlayerState::JUMP_START;
	}

	return state;
}

void TitlePlayerStateRun::Enter(TitlePlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(TitlePlayerState::RUN));
	// state��DEAD��Ԃɂ��ĕۑ�
	state = TitlePlayerState::RUN;
	// �J�E���g���Z�b�g
	jumpDelayCount = 0;
	jumpCount = _owner->GetJumpCount();

}

void TitlePlayerStateRun::JumpDelayProcess(TitlePlayerObject* _owner)
{
	// �W�����v����Ԋu�𐔂���
	++jumpDelayCount;

	// ���Ԃ�������W�����v�����W�����v�J�n�A�j���[�V�������Đ�
	if (jumpDelayCount >= JumpDelayTime)
	{
		// �W�����v�t���O��true��
		_owner->SetJumpFlag(true);
		++jumpCount;
	}
}
