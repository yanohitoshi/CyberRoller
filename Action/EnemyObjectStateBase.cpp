#include "EnemyObjectStateBase.h"

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