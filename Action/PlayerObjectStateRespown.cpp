//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateRespown.h"
#include "SkeletalMeshComponent.h"

/*
@fn コンストラクタ
*/
PlayerObjectStateRespown::PlayerObjectStateRespown()
{
}

/*
@fn デストラクタ
*/
PlayerObjectStateRespown::~PlayerObjectStateRespown()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
PlayerState PlayerObjectStateRespown::Update(PlayerObject* _owner, float _deltaTime)
{

	// ownerのリスポーンフラグをfalseにセット
	_owner->SetRespawnFlag(false);
	// ownerを入力可能状態にセット
	_owner->SetIsAvailableInput(true);

	// ステータスをアイドリング状態に変更する
	state = PlayerState::PLAYER_STATE_IDLE;

	// 更新されたstateを返す
	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void PlayerObjectStateRespown::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_IDLE));
	// stateをリスポーン状態にして保存
	state = PlayerState::PLAYER_STATE_RESPAWN;
}
