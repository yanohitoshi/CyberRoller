//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "FallExplosionObjectStateRespawn.h"
#include "MeshComponent.h"

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return ExplosionObjectState　更新終了時のステータスを返す
*/
ExplosionObjectState FallExplosionObjectStateRespawn::Update(ExplosionObjectBase* _owner, float _deltaTime)
{
	// 時間計測
	++respawnCount;

	// 時間が来たら
	if (respawnCount > RespownTime)
	{
		// 初期化
		_owner->SetIsHitExplosionObject(false);
		meshComponent->SetVisible(true);
		meshComponent->SetEmissiveColor(EmissiveColorBlue);
		_owner->SetRotation(Quaternion::Identity);
		_owner->SetScaleZ(5.0f);
		state = ExplosionObjectState::IDLE;
	}

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void FallExplosionObjectStateRespawn::Enter(ExplosionObjectBase* _owner, float _deltaTime)
{
	state = ExplosionObjectState::RESPAWN;
	firstPosition = _owner->GetFirstPosition();
	respawnCount = 0;
	meshComponent = _owner->GetMeshComponent();
	_owner->SetIsExplode(false);
	_owner->SetState(State::Disabling);

	// ランダムなポジションをセット
	SetRandPosition(_owner);
	// ランダムな落下速度をセット
	SetRandFallSpeed(_owner);
}

/*
@fn ランダムなポジションをセット
@param	_owner 親クラスのポインタ
*/
void FallExplosionObjectStateRespawn::SetRandPosition(ExplosionObjectBase* _owner)
{
	Vector3 fallArea = Vector3::Zero;

	// 落下エリア内でランダムの値を取得
	fallArea = _owner->GetFallArea();
	float randValueX = (float)(rand() % (int)(fallArea.x / 2.0f));
	float randValueY = (float)(rand() % (int)(fallArea.y / 2.0f));

	// 0～3までのランダムを取得
	int plus_minus_value = rand() % 4;

	// 仮ポジション変数に初期位置を代入
	Vector3 tmpPosition = firstPosition;

	// ランダムの値を見てx軸y軸のプラスマイナスを設定
	switch (plus_minus_value)
	{
	case(0):
		tmpPosition.x += randValueX;
		tmpPosition.y += randValueY;
		break;
	case(1):
		tmpPosition.x += randValueX;
		tmpPosition.y -= randValueY;
		break;
	case(2):
		tmpPosition.x -= randValueX;
		tmpPosition.y += randValueY;
		break;
	case(3):
		tmpPosition.x -= randValueX;
		tmpPosition.y -= randValueY;
		break;
	}
	_owner->SetPosition(tmpPosition);
}

/*
@fn ランダムな落下速度をセット
@param	_owner 親クラスのポインタ
*/
void FallExplosionObjectStateRespawn::SetRandFallSpeed(ExplosionObjectBase* _owner)
{
	_owner->SetFallSpeed((float)(rand() % (int)(MaxFallSpeed) +LowestFallSpeed));
}
