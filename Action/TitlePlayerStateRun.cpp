#include "TitlePlayerStateRun.h"
#include "TitlePlayerObject.h"
#include "SkeletalMeshComponent.h"

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return TitlePlayerState　更新終了時のステータスを返す
*/
TitlePlayerState TitlePlayerStateRun::Update(TitlePlayerObject* _owner, float _deltaTime)
{
	// 初期ポジションに戻ってきているか判定
	if (_owner->GetPosition().y >= initPosition.y + CorrectionValuePositionY)
	{
		// 戻ってきていなかったら線形補完を取りながら移動継続
		// 仮ポジション変数
		Vector3 tmpPosition;
		// 線形補完をとり変数に保存
		tmpPosition = Vector3::Lerp(_owner->GetPosition(), initPosition, _deltaTime);
		// ポジションをセット
		_owner->SetPosition(tmpPosition);
	}
	else
	{
		// 戻ってきていたらジャンプ可能状態に
		isAvailableJump = true;
	}
	
	JumpDelayProcess(_owner);

	// ジャンプフラグを判定
	if (_owner->GetJumpFlag())
	{
		_owner->SetJumpCount(jumpCount);
		state = TitlePlayerState::JUMP_START;
	}

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void TitlePlayerStateRun::Enter(TitlePlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(TitlePlayerState::RUN));
	// stateをDEAD状態にして保存
	state = TitlePlayerState::RUN;

	// 初期化
	jumpDelayCount = 0;
	isAvailableJump = false;
	jumpCount = _owner->GetJumpCount();
	initPosition = _owner->GetInitPosition();
}

/*
@fn ジャンプディレイ処理関数
@param	_owner 親クラスのポインタ
*/
void TitlePlayerStateRun::JumpDelayProcess(TitlePlayerObject* _owner)
{
	// ジャンプする間隔を数える
	++jumpDelayCount;

	// 時間が来たらジャンプさせジャンプ開始アニメーションを再生
	if (jumpDelayCount >= JumpDelayTime && isAvailableJump)
	{
		// ジャンプフラグをtrueに
		_owner->SetJumpFlag(true);
		++jumpCount;
	}
}