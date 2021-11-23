//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "FallExplosionObjectStateIdle.h"

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return ExplosionObjectState　更新終了時のステータスを返す
*/
ExplosionObjectState FallExplosionObjectStateIdle::Update(ExplosionObjectBase* _owner, float _deltaTime)
{
	// 元のscaleサイズよりも今のscaleサイズの方が大きかったら
	if (nowScaleZ > OriginalScale)
	{
		// scaleサイズを減らす
		nowScaleZ -= SubScale;
		_owner->SetScaleZ(nowScaleZ);
	}
	else
	{
		// ステータスをActiveにする
		_owner->SetState(State::Active);
	}

	// 落下開始状態で無かったら
	if (!_owner->GetIsFallStart())
	{
		// そのままステートを返す
		return state;
	}

	// 待機時間を数える
	++stayCount;

	// 待機時間を超えていて落下開始状態だったら
	if (stayCount >= StayTime && _owner->GetIsFallStart())
	{
		// ステータスを落下状態に遷移
		state = ExplosionObjectState::FALL;
	}

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void FallExplosionObjectStateIdle::Enter(ExplosionObjectBase* _owner, float _deltaTime)
{
	// ステータスをアイドリング状態にセット
	state = ExplosionObjectState::IDLE;

	// 変数初期化
	rate = 0.0f;
	angle = 0.0f;
	nowScaleZ = _owner->GetScaleVec().z;
	stayCount = 0;
}
