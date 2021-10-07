//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"

/*
@fn 前方ベクトルを用いてキャラクターを回転させる関数
@param	_owner 親クラスのポインタ
@param	_forward 今のフレームの前方ベクトル
@param	_tmpForward 前のフレームの前方ベクトル
*/
void EnemyObjectStateBase::RotationProcess(EnemyObjectBase* _owner, Vector3 _forward, Vector3 _tmpForward)
{
	// 前方ベクトルが前のフレームから変わっていたら
	if (_tmpForward != _forward)
	{
		//前のフレームと今のフレームの前方ベクトルで線形補間を取る
		Vector3 rotatioin = Vector3::Lerp(_forward, _tmpForward, 0.01f);

		// 回転軸を求める
		_owner->RotateToNewForward(rotatioin);
		// 前方ベクトル更新
		_owner->SetCharaForwardVec(rotatioin);
	}
}