//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateDownOver.h"
#include "SkeletalMeshComponent.h"

/*
@fn コンストラクタ
*/
PlayerObjectStateDownOver::PlayerObjectStateDownOver()
{
}

/*
@fn デストラクタ
*/
PlayerObjectStateDownOver::~PlayerObjectStateDownOver()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
PlayerState PlayerObjectStateDownOver::Update(PlayerObject* _owner, float _deltaTime)
{
	// 更新されたstateを返す
	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void PlayerObjectStateDownOver::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DOWN_OVER));
	// stateをゲームオーバー状態にして保存
	state = PlayerState::PLAYER_STATE_DOWN_OVER;
}
