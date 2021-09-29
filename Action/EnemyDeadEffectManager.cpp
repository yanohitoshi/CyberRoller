#include "EnemyDeadEffectManager.h"
#include "EnemyDeadEffect.h"
#include "EnemyObjectBase.h"
#include "EnemyExplosionEffect.h"

EnemyDeadEffectManager::EnemyDeadEffectManager(EnemyObjectBase* _owner)
	: GameObject(false, Tag::PARTICLE)
	, MaxEffects(1)
	, MaxExplosionEffects(50)
	, RandValueX(250)
	, RandValueY(250)
	, RandValueZ(250)
	, CorrectionRandValue(10.0f)
	, LastCorrection(0.1f)
{
	// メンバー変数の初期化	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	generateExplosionEffectsFlag = true;
	frameCount = 0;
}

EnemyDeadEffectManager::~EnemyDeadEffectManager()
{
}

void EnemyDeadEffectManager::UpdateGameObject(float _deltaTime)
{
	// 前のフレームでZ軸の速度が0.0fでなくこのフレームでのZ軸の速度0.0fでかつジャンプフラグがfalseだったら
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

	++frameCount;
	if (frameCount >= 15)
	{
		GenerateEffectProcess();
		frameCount = 0;
	}
}

void EnemyDeadEffectManager::GenerateEffectProcess()
{
	// ownerのポジションを得る
	position = owner->GetPosition();

	velocity = Vector3::UnitZ;

	for (int efectCount = 0; efectCount < MaxEffects; efectCount++)
	{
		//particleを生成
		new EnemyDeadEffect(owner,position);
	}

	if (generateExplosionEffectsFlag)
	{
		for (int explosionEfectCount = 0; explosionEfectCount < MaxExplosionEffects; explosionEfectCount++)
		{
			// ランダムな値を生成
			Vector3 randV((rand() % RandValueX) / CorrectionRandValue, (rand() % RandValueY) / CorrectionRandValue, (rand() % RandValueZ) / CorrectionRandValue);

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

			//particleを生成
			new EnemyExplosionEffect(owner, position, velocity);
		}
		generateExplosionEffectsFlag = false;
	}
}

