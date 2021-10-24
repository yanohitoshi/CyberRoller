#include "TitlePlayerStateJumpLoop.h"
#include "TitlePlayerObject.h"
#include "SkeletalMeshComponent.h"
#include "TitleJumpAttackPlayerObject.h"

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return TitlePlayerState　更新終了時のステータスを返す
*/
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

	// 重力をかける
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

	// 上下方向の速度が0以下でジャンプした回数が3以上なら
	if (velocity.z <= 0.0f && _owner->GetJumpCount() >= 3)
	{
		// ジャンプした回数を初期化
		_owner->SetJumpCount(0);
		// ステータスをジャンプアタックに変更
		state = TitlePlayerState::JUMP_ATTACK;
	}

	// ポジションが接地位置より小さくなっていたら
	if (_owner->GetPosition().z <= OnGroundCoordinate)
	{
		// ジャンプフラグをfalseに
		_owner->SetJumpFlag(false);
		// ステータスを走り状態に
		state = TitlePlayerState::RUN;
	}

    return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void TitlePlayerStateJumpLoop::Enter(TitlePlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(TitlePlayerState::JUMP_LOOP));

	if (!skeletalMeshComponent->GetVisible())
	{
		skeletalMeshComponent->SetVisible(true);
	}

	// オーナーからタイトル用ジャンプアタックプレイヤーのポインタをもらう
	titleJumpAttackPlayerObject = _owner->GetTitleJumpAttackPlayerObject();
	// タイトル用ジャンプアタックプレイヤーからmeshComponentのポインタをもらう
	meshComponent = titleJumpAttackPlayerObject->GetMeshComponent();
	if (meshComponent->GetVisible())
	{
		meshComponent->SetVisible(false);
	}
	// stateをDEAD状態にして保存
	state = TitlePlayerState::JUMP_LOOP;

	// 初期化
	jumpFrameCount = _owner->GetJumpFrameCount();
	jumpPower = _owner->GetJumpPower();
}