#include "BreakBlockObjectEffectManager.h"
#include "BreakBlockObject.h"
#include "DustEffect.h"
#include "DebrisEffectObject.h"

BreakBlockObjectEffectManager::BreakBlockObjectEffectManager(BreakBlockObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, DustEffectRandValue(250)
	, CorrectionRandValue(10.0f)
	, LastCorrection(0.1f)
{
	// メンバー変数の初期化	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	generateExplosionEffectsFlag = true;
	activeCount = 0;
}

BreakBlockObjectEffectManager::~BreakBlockObjectEffectManager()
{
}

void BreakBlockObjectEffectManager::UpdateGameObject(float _deltaTime)
{
	// 死亡状態だったら有効化
	if (owner->GetState() == State::Disabling)
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
		activeCount = 0;
		generateExplosionEffectsFlag = true;
		break;

		// 有効状態だったら
	case PARTICLE_ACTIVE:

		// エフェクトの生成
		ActiveEffectProcess();
		break;
	}
}

void BreakBlockObjectEffectManager::ActiveEffectProcess()
{

	if (generateExplosionEffectsFlag)
	{
		effectPosition = owner->GetPosition();
		GenerateDustEffectProcess();
		GenerateDebrisEffectProcess();
		generateExplosionEffectsFlag = false;
	}
}

void BreakBlockObjectEffectManager::GenerateDustEffectProcess()
{
	for (int dustEfectCount = 0; dustEfectCount < 20; dustEfectCount++)
	{
		// ランダムな値を生成
		Vector3 randV((rand() % DustEffectRandValue) / CorrectionRandValue, (rand() % DustEffectRandValue) / CorrectionRandValue, (rand() % DustEffectRandValue) / CorrectionRandValue);

		// 値が大きすぎるので最後の補正をかけて速度に代入
		effectVelocity = randV * LastCorrection;
		effectVelocity.Normalize();

		if (dustEfectCount % 2 == 0)
		{
			effectVelocity.x *= -1.0f;
			effectVelocity.z *= -1.0f;
		}

		if (dustEfectCount % 3 == 0)
		{
			effectVelocity.y *= -1.0f;
		}

		//エフェクトを生成
		new DustEffect(this, effectPosition, effectVelocity);
	}
}

void BreakBlockObjectEffectManager::GenerateDebrisEffectProcess()
{
	for (int i = 0; i < 20; i++)
	{
		// ランダムな値を生成
		Vector3 randDir((float)(rand() % 50), (float)(rand() % 50), 1.0f);
		randDir.Normalize();

		if (i % 2 == 0)
		{
			randDir.x *= -1.0f;
		}

		if (i % 3 == 0)
		{
			randDir.y *= -1.0f;
		}

		randDir.z = 1.0f;

		new DebrisEffectObject(effectPosition, randDir);
	}
}
