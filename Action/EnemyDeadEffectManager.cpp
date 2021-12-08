//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyDeadEffectManager.h"
#include "EnemyElectricShockEffect.h"
#include "EnemyObjectBase.h"
#include "EnemyExplosionEffect.h"

/*
@fn コンストラクタ
@param	_owner 親クラスのポインタ
*/
EnemyDeadEffectManager::EnemyDeadEffectManager(EnemyObjectBase* _owner)
	: GameObject(false, Tag::PARTICLE)
	, WaitingExplosionTime(49)
	, MaxExplosionEffects(10)
	, RandValue(250)
	, CorrectionRandValue(10.0f)
	, LastCorrection(0.1f)
	, TowFrequency(2)
	, ThreeFrequency(3)
	, FiveFrequency(5)
{
	// メンバー変数の初期化	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	generateExplosionEffectsFlag = true;
	effectFrameCount = 0;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
EnemyDeadEffectManager::~EnemyDeadEffectManager()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void EnemyDeadEffectManager::UpdateGameObject(float _deltaTime)
{

	// 死亡状態だったら有効化
	if (owner->GetIsDead() && owner->GetIsVisible())
	{
		// パーティクルを有効化
		particleState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		// パーティクルを無効化
		particleState = ParticleState::PARTICLE_DISABLE;
	}

	// パーティクルの状態を見て
	switch (particleState)
	{
		// 無効状態だったらbreak
	case (PARTICLE_DISABLE):
		effectFrameCount = 0;
		generateExplosionEffectsFlag = true;
		break;

		// 有効状態だったら
	case PARTICLE_ACTIVE:

		// エフェクトの生成
		ActiveEffect();
		break;
	}
}

/*
@fn エフェクトがアクティブ時の処理関数
*/
void EnemyDeadEffectManager::ActiveEffect()
{
	++effectFrameCount;

	if (effectFrameCount % FiveFrequency == 0)
	{
		GenerateEffect();
	}
}

/*
@fn エフェクト生産処理関数
*/
void EnemyDeadEffectManager::GenerateEffect()
{
	// ownerのポジションを得る
	position = owner->GetPosition();

	if (generateExplosionEffectsFlag && effectFrameCount >= WaitingExplosionTime)
	{
		GenerateExplosionEffectProcess();

		generateExplosionEffectsFlag = false;
	}
	else
	{
		velocity = Vector3::UnitZ;
		//エフェクトを生成
		new EnemyElectricShockEffect(owner, position);
	}
}

/*
@fn 爆発エフェクト生産処理関数
*/
void EnemyDeadEffectManager::GenerateExplosionEffectProcess()
{
	velocity = Vector3::Zero;

	for (int explosionEfectCount = 0; explosionEfectCount < MaxExplosionEffects; explosionEfectCount++)
	{
		// ランダムな値を生成
		Vector3 randV((rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue);

		// 値が大きすぎるので最後の補正をかけて速度に代入
		velocity = randV * LastCorrection;
		velocity.Normalize();

		if (explosionEfectCount % TowFrequency == 0)
		{
			velocity.x *= -1.0f;
			velocity.z *= -1.0f;
		}

		if (explosionEfectCount % ThreeFrequency == 0)
		{
			velocity.y *= -1.0f;
		}

		//エフェクトを生成
		new EnemyExplosionEffect(owner, position, velocity);
	}
}