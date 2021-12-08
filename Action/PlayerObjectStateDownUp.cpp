//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateDownUp.h"
#include "SkeletalMeshComponent.h"

/*
@fn コンストラクタ
*/
PlayerObjectStateDownUp::PlayerObjectStateDownUp()
{
}

/*
@fn デストラクタ
*/
PlayerObjectStateDownUp::~PlayerObjectStateDownUp()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return PlayerState　更新終了時のステータスを返す
*/
PlayerState PlayerObjectStateDownUp::Update(PlayerObject* _owner, float _deltaTime)
{
	// 更新されたstateを返す
    return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void PlayerObjectStateDownUp::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DOWN_UP));
	// stateをコンティニュー状態にして保存
	state = PlayerState::PLAYER_STATE_DOWN_UP;
}