#include "TitlePlayerStateJumpStart.h"
#include "TitlePlayerObject.h"
#include "SkeletalMeshComponent.h"

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return TitlePlayerState　更新終了時のステータスを返す
*/
TitlePlayerState TitlePlayerStateJumpStart::Update(TitlePlayerObject* _owner, float _deltaTime)
{
	// ジャンプ中のカウントを数える
	++jumpFrameCount;
	// さらにジャンプ力を追加
	jumpPower += JumpSpeed;
	// 重力を掛ける
	jumpPower -= Gravity * _deltaTime;

	// ジャンプ力を追加
	velocity.z = jumpPower;

	// 落下速度が規定値を超えていたら
	if (velocity.z <= MaxFallSpeed)
	{
		// 落下速度を規定値に固定する
		velocity.z = MaxFallSpeed;
	}

	// ポジションを更新
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// animationが終了していたら
	if (!skeletalMeshComponent->IsPlaying())
	{
		// ジャンプした回数を加算
		++jumpCount;
		// 親クラスに値をセット
		_owner->SetJumpCount(jumpCount);
		_owner->SetJumpPower(jumpPower);
		_owner->SetJumpFrameCount(jumpFrameCount);
		// ステータスをジャンプループに変更
		state = TitlePlayerState::JUMP_LOOP;
	}

    return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void TitlePlayerStateJumpStart::Enter(TitlePlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(TitlePlayerState::JUMP_START));
	// stateをDEAD状態にして保存
	state = TitlePlayerState::JUMP_START;
	// 初期化
	jumpPower = FirstJumpPower;
	jumpFrameCount = 0;
	jumpCount = _owner->GetJumpCount();
}