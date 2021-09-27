#include "EnemyDeadEffectManager.h"
#include "EnemyDeadEffect.h"
#include "EnemyObjectBase.h"

EnemyDeadEffectManager::EnemyDeadEffectManager(EnemyObjectBase* _owner)
	: GameObject(false, Tag::PARTICLE)
	, MaxEffects(3)
{
	// メンバー変数の初期化	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	generateFlag = true;
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
		generateFlag = true;
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
	if (frameCount >= 10)
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
}

