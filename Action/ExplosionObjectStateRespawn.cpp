//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateRespawn.h"
#include "MeshComponent.h"

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return ExplosionObjectState　更新終了時のステータスを返す
*/
ExplosionObjectState ExplosionObjectStateRespawn::Update(ExplosionObjectBase* _owner, float _deltaTime)
{
	// 時間計測
	++respawnCount;

	// 時間が来たら
	if (respawnCount > RespownTime)
	{
		//初期化
		_owner->SetIsHitExplosionObject(false);
		meshComponent->SetVisible(true);
		meshComponent->SetEmissiveColor(EmissiveColorBlue);
		_owner->SetRotation(Quaternion::Identity);
		_owner->SetScaleZ(5.0f);
		_owner->SetPosition(firstPosition);
		// ステータスをアイドリングに
		state = ExplosionObjectState::IDLE;
	}

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void ExplosionObjectStateRespawn::Enter(ExplosionObjectBase* _owner, float _deltaTime)
{
	// ステータスをリスポーン状態に遷移
	state = ExplosionObjectState::RESPAWN;
	// 変数初期化
	firstPosition = _owner->GetFirstPosition();
	respawnCount = 0;
	meshComponent = _owner->GetMeshComponent();
	_owner->SetIsExplode(false);
	_owner->SetState(State::Disabling);
}