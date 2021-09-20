#include "AfterimageEffectManager.h"
#include "AfterimageEffect.h"

AfterimageEffectManager::AfterimageEffectManager(GameObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, MaxEffects(50)
	, RandValue(100)
{
	// メンバー変数の初期化	
	owner = _owner;
	position = owner->GetPosition();
	generateFlag = true;
	velocity = Vector3::Zero;
	effectPosition = Vector3::Zero;
}

AfterimageEffectManager::~AfterimageEffectManager()
{
}

void AfterimageEffectManager::UpdateGameObject(float _deltaTime)
{
	//// 親クラスのステータスがActiveだったら
	//if (owner->GetNowState() == PlayerState::PLAYER_STATE_JUMP_ATTACK)
	//{
	//	// particleStateを有効化
	//	particleState = ParticleState::PARTICLE_ACTIVE;
	//}
	//else
	//{
	//	// particleStateを無効化
	//	particleState = ParticleState::PARTICLE_DISABLE;
	//}

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

void AfterimageEffectManager::ActiveEffectProcess()
{
	// ownerのポジションを得る
	effectPosition = owner->GetPosition();

	// 生成フラグがtrueだったら
	if (generateFlag == true)
	{
		// エフェクト生産関数
		GenerateEffectProcess();

		// 生成フラグをfalseに
		generateFlag = false;
	}

}

void AfterimageEffectManager::GenerateEffectProcess()
{

	for (int efectCount = 0; efectCount < MaxEffects; efectCount++)
	{

		// ランダムな値を生成
		Vector3 randV((rand() % RandValue), (rand() % RandValue), (rand() % RandValue));
		// 値が大きすぎるので最後の補正をかけて速度に代入
		velocity = randV /** LastCorrection*/;
		velocity.Normalize();

		//// 速度を一時保存設定
		//Vector3 vel = velocity;

		////ランダムな値を渡す
		//vel = vel + randV;
		//// 下に落としたいのでZ軸はマイナスに
		//vel.z *= -1.0f;

		if (MaxEffects % 2 == 0)
		{
			velocity.x *= -1.0f;
		}
		else if (MaxEffects % 3 == 0)
		{
			velocity.y *= -1.0f;
		}

		new AfterimageEffect(effectPosition, velocity);
	}

}