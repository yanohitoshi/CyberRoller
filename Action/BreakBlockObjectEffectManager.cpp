#include "BreakBlockObjectEffectManager.h"
#include "BreakBlockObject.h"
#include "DustEffect.h"

BreakBlockObjectEffectManager::BreakBlockObjectEffectManager(BreakBlockObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	//, WaitingExplosionTime(49)
	//, MaxExplosionEffects(10)
	//, RandValue(250)
	//, CorrectionRandValue(10.0f)
	//, LastCorrection(0.1f)
{
	// メンバー変数の初期化	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	generateExplosionEffectsFlag = true;
	//effectFrameCount = 0;
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

void BreakBlockObjectEffectManager::ActiveEffectProcess()
{

	if (generateExplosionEffectsFlag)
	{
		effectPosition = owner->GetPosition();
		new DustEffect(this, effectPosition, effectVelocity);
		generateExplosionEffectsFlag = false;
	}
}

void BreakBlockObjectEffectManager::GenerateEffectProcess()
{
}

void BreakBlockObjectEffectManager::GenerateExplosionEffectProcess()
{
}
