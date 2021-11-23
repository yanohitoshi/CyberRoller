//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateFall.h"
#include "MeshComponent.h"

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return ExplosionObjectState　更新終了時のステータスを返す
*/
ExplosionObjectState ExplosionObjectStateFall::Update(ExplosionObjectBase* _owner, float _deltaTime)
{
	// 落ちる時間をカウント
	++fallCount;

	// 落ちる速度を代入
	velocity.z = -fallSpeed;

	// ポジション更新
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// 点滅処理
	Flashing();

	// 爆発するオブジェクトに当たるかZ軸が0.0f以下になったら
	if (_owner->GetIsHitExplosionObject() || _owner->GetPosition().z < 0.0f)
	{
		// ステータスを爆発状態に遷移
		state = ExplosionObjectState::EXPLOSION;
		return state;
	}

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void ExplosionObjectStateFall::Enter(ExplosionObjectBase* _owner, float _deltaTime)
{
	// ステータスを落下状態に変更
	state = ExplosionObjectState::FALL;
	meshComponent = _owner->GetMeshComponent();
	// 速度を初期化
	velocity = Vector3::Zero;
	isRed = false;
	colorChangeTime = FirstColorChangeTime;
	fallCount = 0;
	angle = 0;
	_owner->SetState(State::Active);
	fallSpeed = _owner->GetFallSpeed();
}

/*
@fn 点滅処理
*/
void ExplosionObjectStateFall::Flashing()
{
	// タイミングを変える時間が来たら
	if (fallCount > FirstChangeRateTime)
	{
		// 二番目の色を変える時間を代入
		colorChangeTime = SecondColorChangeTime;
	}

	if (fallCount > SecondChangeRateTime)
	{
		// 三番目の色を変える時間を代入
		colorChangeTime = ThirdColorChangeTime;
	}

	// 色を変更するタイミングが来たら
	if (fallCount % colorChangeTime == 0)
	{
		// 色フラグを変更
		if (isRed)
		{
			isRed = false;
		}
		else
		{
			isRed = true;
		}
	}

	// 色情報を更新
	if (isRed)
	{
		meshComponent->SetEmissiveColor(EmissiveColorRed);
	}
	else
	{
		meshComponent->SetEmissiveColor(EmissiveColorBlue);
	}
}
