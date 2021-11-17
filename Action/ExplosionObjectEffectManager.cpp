#include "ExplosionObjectEffectManager.h"
#include "ExplosionObjectBase.h"
#include "ExplosionEffect.h"
#include "ExplosionRipplesEffect.h"
#include "SplashExplosionEffect.h"

ExplosionObjectEffectManager::ExplosionObjectEffectManager(ExplosionObjectBase* _owner)
	: GameObject(false, Tag::PARTICLE)
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
}

ExplosionObjectEffectManager::~ExplosionObjectEffectManager()
{
}

void ExplosionObjectEffectManager::UpdateGameObject(float _deltaTime)
{
	// 死亡状態だったら有効化
	if (owner->GetIsExplode())
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
		//effectFrameCount = 0;
		generateExplosionEffectsFlag = true;
		break;

		// 有効状態だったら
	case PARTICLE_ACTIVE:

		// エフェクトの生成
		ActiveEffectProcess();
		break;
	}
}

void ExplosionObjectEffectManager::ActiveEffectProcess()
{
	
	if (generateExplosionEffectsFlag)
	{
		velocity = Vector3::Zero;
		effectPosition = owner->GetPosition();

		for (int i = 0; i < 2; i++)
		{
			new ExplosionRipplesEffect(this, effectPosition);
		}

		GenerateExplosionEffectProcess();

		generateExplosionEffectsFlag = false;
	}
}

void ExplosionObjectEffectManager::GenerateEffectProcess()
{
}

void ExplosionObjectEffectManager::GenerateExplosionEffectProcess()
{
	//エフェクトを生成
	new ExplosionEffect(effectPosition, effectVelocity);

	for (int explosionEfectCount = 0; explosionEfectCount < MaxExplosionEffects; explosionEfectCount++)
	{
		// ランダムな値を生成
		Vector3 randV((rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue);

		// 値が大きすぎるので最後の補正をかけて速度に代入
		effectVelocity = randV * LastCorrection;
		effectVelocity.Normalize();

		if (explosionEfectCount % 2 == 0)
		{
			effectVelocity.x *= -1.0f;
			effectVelocity.z *= -1.0f;
		}

		if (explosionEfectCount % 3 == 0)
		{
			effectVelocity.y *= -1.0f;
		}

		new SplashExplosionEffect(effectPosition, effectVelocity);
	}
}
