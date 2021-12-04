//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateStartExplosion.h"
#include "MeshComponent.h"
#include "SoundEffectComponent.h"

ExplosionObjectStateStartExplosion::ExplosionObjectStateStartExplosion(ExplosionObjectBase* _owner)
	: BlowAwaySpeed(1600.0f)
	, FirstColorChangeTime(15)
	, ExplosionStartTime(180)
{
	soundEffectComponent = new SoundEffectComponent(_owner, "Assets/Sound/SoundEffect/Explosion/Explosion2.wav");
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return ExplosionObjectState　更新終了時のステータスを返す
*/
ExplosionObjectState ExplosionObjectStateStartExplosion::Update(ExplosionObjectBase* _owner, float _deltaTime)
{
	// 時間計測
	++explosionStart;

	// ジャンプアタックプレイヤーに降れていなければ
	if (!isHitJumpAttackPlayer)
	{
		// 時間が来るまでその場で停止
		if (explosionStart > ExplosionStartTime)
		{
			// 時間が来たら爆発
			state = ExplosionObjectState::EXPLOSION;
			return state;
		}

	}
	else
	{
		// 時間がくるもしくは当たったら即爆発するオブジェクトに触れたら
		if (explosionStart > ExplosionStartTime || _owner->GetIsHitExplosionObject())
		{
			// 爆発
			state = ExplosionObjectState::EXPLOSION;
			return state;
		}
		// 時間内は回転しながら移動
		velocity = blowAwayDirection * BlowAwaySpeed;
		_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
		angle += 0.1f;
		RotationProcess(_owner, angle, Vector3::UnitY);
	}

	// 点滅処理
	Flashing();

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void ExplosionObjectStateStartExplosion::Enter(ExplosionObjectBase* _owner, float _deltaTime)
{
	// ステータスを爆発開始状態にセット
	state = ExplosionObjectState::EXPLOSION_START;
	meshComponent = _owner->GetMeshComponent();
	// 速度を初期化
	velocity = Vector3::Zero;

	// 吹っ飛ぶ方向を計算
	isHitJumpAttackPlayer = _owner->GetIsHitJumpAttackPlayer();
	blowAwayDirection = _owner->GetPosition() - _owner->GetHitPosition();
	if (!Math::NearZero(blowAwayDirection.Length()))
	{
		blowAwayDirection.Normalize();
	}
	blowAwayDirection.z = 0.0f;

	// 変数初期化
	isRed = false;
	colorChangeTime = FirstColorChangeTime;
	explosionStart = 0;
	angle = 0;
	_owner->SetState(State::Disabling);

	//// 効果音を鳴らす
	//soundEffectComponent->Play();

}

void ExplosionObjectStateStartExplosion::Flashing()
{
	// タイミングを変える時間が来たら
	if (explosionStart > FirstChangeRateTime)
	{
		// 二番目の色を変える時間を代入
		colorChangeTime = SecondColorChangeTime;
	}

	if (explosionStart > SecondChangeRateTime)
	{
		// 三番目の色を変える時間を代入
		colorChangeTime = ThirdColorChangeTime;
	}

	// 色を変更するタイミングが来たら
	if (explosionStart % colorChangeTime == 0)
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
