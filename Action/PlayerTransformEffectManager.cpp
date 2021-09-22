#include "PlayerTransformEffectManager.h"
#include "PlayerTransformEffect.h"
#include "PlayerObject.h"

PlayerTransformEffectManager::PlayerTransformEffectManager(PlayerObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, MaxEffects(20)
	, RandValue(100)
{
	// メンバー変数の初期化	
	owner = _owner;
	position = owner->GetPosition();
	generateFlag = true;
	velocity = Vector3::Zero;
	effectPosition = Vector3::Zero;
	frameCount = 0;
	effectCount = 0;
}

PlayerTransformEffectManager::~PlayerTransformEffectManager()
{
}

void PlayerTransformEffectManager::UpdateGameObject(float _deltaTime)
{
	// 親クラスのステータスがActiveだったら
	if (owner->GetNowState() == PlayerState::PLAYER_STATE_JUMP_ATTACK)
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
	case (PARTICLE_DISABLE):
		// 初期化
		generateFlag = true;
		break;

		// 有効状態だったら
	case PARTICLE_ACTIVE:

		ActiveEffectProcess();

		break;
	}
}

void PlayerTransformEffectManager::ActiveEffectProcess()
{

	// 生成フラグがtrueだったら
	if (generateFlag == true)
	{
		++frameCount;
		if (frameCount % 2 == 0)
		{
			// エフェクト生産関数
			GenerateEffectProcess();
		}

		if (effectCount >= 3)
		{
			effectCount = 0;
			frameCount = 0;
			// 生成フラグをfalseに
			generateFlag = false;
		}
	}

}

void PlayerTransformEffectManager::GenerateEffectProcess()
{
	
	// ownerのポジションを得る
	effectPosition = owner->GetPosition();
	effectPosition.z += 100.0f;
	new PlayerTransformEffect(effectPosition, velocity);
	++effectCount;
}
