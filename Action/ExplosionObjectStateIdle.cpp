//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateIdle.h"

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return ExplosionObjectState　更新終了時のステータスを返す
*/
ExplosionObjectState ExplosionObjectStateIdle::Update(ExplosionObjectBase* _owner, float _deltaTime)
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
		// ステータスをActiveに変更
		_owner->SetState(State::Active);
		// 垂直移動処理
		VerticalMove(_owner, _deltaTime);
	}

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void ExplosionObjectStateIdle::Enter(ExplosionObjectBase* _owner, float _deltaTime)
{
	// ステータスをアイドリング状態にする
	state = ExplosionObjectState::IDLE;
	// 変数初期化
	rate = 0.0f;
	angle = 0.0f;
	nowScaleZ = _owner->GetScaleVec().z;
}
