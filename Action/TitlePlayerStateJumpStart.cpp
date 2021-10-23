#include "TitlePlayerStateJumpStart.h"
#include "TitlePlayerObject.h"
#include "SkeletalMeshComponent.h"

TitlePlayerState TitlePlayerStateJumpStart::Update(TitlePlayerObject* _owner, float _deltaTime)
{

	// 重力を掛ける
	velocity.z -= Gravity * _deltaTime;

	// 落下速度が規定値を超えていたら
	if (velocity.z <= MaxFallSpeed)
	{
		// 落下速度を規定値に固定する
		velocity.z = MaxFallSpeed;
	}

	// ジャンプ中のカウントを数える
	++jumpFrameCount;
	// さらにジャンプ力を追加
	jumpPower += JumpSpeed;
	// ジャンプ力を追加
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
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(TitlePlayerState::JUMP_START));
	// stateをDEAD状態にして保存
	state = TitlePlayerState::JUMP_START;
	jumpPower = FirstJumpPower;
	jumpFrameCount = 0;
}
