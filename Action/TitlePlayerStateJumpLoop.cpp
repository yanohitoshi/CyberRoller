#include "TitlePlayerStateJumpLoop.h"
#include "TitlePlayerObject.h"
#include "SkeletalMeshComponent.h"

TitlePlayerState TitlePlayerStateJumpLoop::Update(TitlePlayerObject* _owner, float _deltaTime)
{
	// �W�����v���̃J�E���g�𐔂���
	++jumpFrameCount;

	// �W�����v���̃J�E���g���K��l�ȉ���������
	if (jumpFrameCount < JumpLimitTime)
	{
		// ����ɃW�����v�͂�ǉ�
		jumpPower += JumpSpeed;
	}

	// �W�����v�͂�ǉ�
	velocity.z = jumpPower;

	_owner->SetPosition(_owner->GetPosition() + velocity);

	if (_owner->GetPosition().z <= OnGroundCoordinate)
	{
		state = TitlePlayerState::RUN;
	}

    return state;
}

void TitlePlayerStateJumpLoop::Enter(TitlePlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(TitlePlayerState::JUMP_LOOP));
	// state��DEAD��Ԃɂ��ĕۑ�
	state = TitlePlayerState::JUMP_LOOP;
	jumpFrameCount = _owner->GetJumpFrameCount();
	jumpPower = _owner->GetJumpPower();
}
