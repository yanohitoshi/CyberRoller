#include "TitlePlayerStateJumpLoop.h"
#include "TitlePlayerObject.h"
#include "SkeletalMeshComponent.h"

TitlePlayerState TitlePlayerStateJumpLoop::Update(TitlePlayerObject* _owner, float _deltaTime)
{
	// ジャンプ中のカウントを数える
	++jumpFrameCount;

	// ジャンプ中のカウントが規定値以下だったら
	if (jumpFrameCount < JumpLimitTime)
	{
		// さらにジャンプ力を追加
		jumpPower += JumpSpeed;
	}

	// ジャンプ力を追加
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
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(TitlePlayerState::JUMP_LOOP));
	// stateをDEAD状態にして保存
	state = TitlePlayerState::JUMP_LOOP;
	jumpFrameCount = _owner->GetJumpFrameCount();
	jumpPower = _owner->GetJumpPower();
}
