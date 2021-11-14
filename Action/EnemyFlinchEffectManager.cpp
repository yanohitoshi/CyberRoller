#include "EnemyFlinchEffectManager.h"
#include "EnemyElectricShockEffect.h"
#include "EnemyObjectBase.h"

EnemyFlinchEffectManager::EnemyFlinchEffectManager(EnemyObjectBase* _owner)
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
	effectFrameCount = 0;
}

EnemyFlinchEffectManager::~EnemyFlinchEffectManager()
{
}

void EnemyFlinchEffectManager::UpdateGameObject(float _deltaTime)
{
	// 死亡状態だったら有効化
	if (owner->GetIsFlinch())
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
		break;

		// 有効状態だったら
	case PARTICLE_ACTIVE:

		// エフェクトの生成
		ActiveEffectProcess();
		break;
	}
}

void EnemyFlinchEffectManager::ActiveEffectProcess()
{
	++effectFrameCount;

	if (effectFrameCount % 5 == 0)
	{
		GenerateEffectProcess();
	}
}

void EnemyFlinchEffectManager::GenerateEffectProcess()
{
	// ownerのポジションを得る
	position = owner->GetPosition();
	//エフェクトを生成
	new EnemyElectricShockEffect(owner, position);
}
