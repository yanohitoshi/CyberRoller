#include "EnemyDeadEffectManager.h"
#include "EnemyDeadEffect.h"
#include "EnemyObjectBase.h"
#include "EnemyExplosionEffect.h"

EnemyDeadEffectManager::EnemyDeadEffectManager(EnemyObjectBase* _owner)
	: GameObject(false, Tag::PARTICLE)
	, WaitingExplosionTime(120)
	, MaxExplosionEffects(10)
	, RandValue(250)
	, CorrectionRandValue(10.0f)
	, LastCorrection(0.1f)
{
	// メンバー変数の初期化	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	generateExplosionEffectsFlag = true;
	effectFrameCount = 0;
}

EnemyDeadEffectManager::~EnemyDeadEffectManager()
{
}

void EnemyDeadEffectManager::UpdateGameObject(float _deltaTime)
{
	// 死亡状態だったら有効化
	if (owner->GetIsDeadFlag())
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
		ActiveEffectProcess();
		break;
	}
}

void EnemyDeadEffectManager::ActiveEffectProcess()
{
	++effectFrameCount;

	if (effectFrameCount % 15 == 0)
	{
		GenerateEffectProcess();
	}
}

void EnemyDeadEffectManager::GenerateEffectProcess()
{
	// ownerのポジションを得る
	position = owner->GetPosition();

	if (generateExplosionEffectsFlag && effectFrameCount >= WaitingExplosionTime)
	{
		velocity = Vector3::Zero;

		for (int explosionEfectCount = 0; explosionEfectCount < MaxExplosionEffects; explosionEfectCount++)
		{
			// ランダムな値を生成
			Vector3 randV((rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue);

			// 値が大きすぎるので最後の補正をかけて速度に代入
			velocity = randV * LastCorrection;
			velocity.Normalize();

			if (explosionEfectCount % 2 == 0)
			{
				velocity.x *= -1.0f;
				velocity.z *= -1.0f;
			}

			if (explosionEfectCount % 3 == 0)
			{
				velocity.y *= -1.0f;
			}

			//エフェクトを生成
			new EnemyExplosionEffect(owner, position, velocity);
		}

		generateExplosionEffectsFlag = false;
	}
	else
	{
		velocity = Vector3::UnitZ;
		//エフェクトを生成
		new EnemyDeadEffect(owner, position);
	}
}

