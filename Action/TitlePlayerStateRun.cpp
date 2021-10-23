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
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(TitlePlayerState::RUN));
	// stateをDEAD状態にして保存
	state = TitlePlayerState::RUN;
	// カウントリセット
	jumpDelayCount = 0;
	jumpCount = _owner->GetJumpCount();

}

void TitlePlayerStateRun::JumpDelayProcess(TitlePlayerObject* _owner)
{
	// ジャンプする間隔を数える
	++jumpDelayCount;

	// 時間が来たらジャンプさせジャンプ開始アニメーションを再生
	if (jumpDelayCount >= JumpDelayTime)
	{
		// ジャンプフラグをtrueに
		_owner->SetJumpFlag(true);
		++jumpCount;
	}
}
