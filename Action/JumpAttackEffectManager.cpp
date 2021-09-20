#include "JumpAttackEffectManager.h"
#include "JumpAttackEffect.h"

JumpAttackEffectManager::JumpAttackEffectManager(GameObject* _owner)
	: GameObject(false, Tag::PARTICLE)
{
	// メンバー変数の初期化	
	owner = _owner;
	position = owner->GetPosition();
	frameCount = 0;
	generateCount = 0;
	effectPosition = Vector3::Zero;
}

JumpAttackEffectManager::~JumpAttackEffectManager()
{
}

void JumpAttackEffectManager::UpdateGameObject(float _deltaTime)
{
	// 親クラスのステータスがActiveだったら
	if (owner->GetState() == State::Active)
	{
		// particleStateを有効化
		particleState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		// particleStateを無効化
		particleState = ParticleState::PARTICLE_DISABLE;
	}

	// パーティクルの状態を見て
	switch (particleState)
	{
		// 無効状態だったら生成カウントを0にしてbreak
	case (PARTICLE_DISABLE):
		break;

		// 有効状態だったら
	case PARTICLE_ACTIVE:

		ActiveEffectProcess();
		break;
	}

}

void JumpAttackEffectManager::ActiveEffectProcess()
{
	// ownerのポジションを得る
	effectPosition = owner->GetPosition();
	GenerateEffectProcess();
}

void JumpAttackEffectManager::GenerateEffectProcess()
{
	// particleを生成
	new JumpAttackEffect(effectPosition, Vector3::Zero);
}
