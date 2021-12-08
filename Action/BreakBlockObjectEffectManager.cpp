//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "BreakBlockObjectEffectManager.h"
#include "BreakBlockObject.h"
#include "DustEffect.h"
#include "DebrisEffectObject.h"

/*
@fn コンストラクタ
@param	_owner 親クラスのポインタ
*/
BreakBlockObjectEffectManager::BreakBlockObjectEffectManager(BreakBlockObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, DustEffectRandValue(250)
	, CorrectionRandValue(10.0f)
	, DustMaxEffect(20)
	, DebrisEffectRandValue(50)
	, DebrisMaxEffect(20)
	, LastCorrection(0.1f)
	, TowFrequency(2)
	, ThreeFrequency(3)
{
	// メンバー変数の初期化	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	generateEffectsFlag = true;
	activeCount = 0;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
BreakBlockObjectEffectManager::~BreakBlockObjectEffectManager()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
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
		generateEffectsFlag = true;
		break;

		// 有効状態だったら
	case PARTICLE_ACTIVE:

		// エフェクトの生成
		ActiveEffect();
		break;
	}
}

/*
@fn エフェクトがアクティブ時の処理関数
*/
void BreakBlockObjectEffectManager::ActiveEffect()
{
	// まだ生成されていなかったら
	if (generateEffectsFlag)
	{
		// ポジション取得
		effectPosition = owner->GetPosition();
		// 埃エフェクト生成
		GenerateDustEffect();
		// 破片エフェクト生成
		GenerateDebrisEffect();
		// 生成フラグをfalseに変更
		generateEffectsFlag = false;
	}
}

/*
@fn 土埃エフェクト生産処理関数
*/
void BreakBlockObjectEffectManager::GenerateDustEffect()
{
	for (int dustEfectCount = 0; dustEfectCount < DustMaxEffect; dustEfectCount++)
	{
		// ランダムな値を生成
		Vector3 randV((rand() % DustEffectRandValue) / CorrectionRandValue, (rand() % DustEffectRandValue) / CorrectionRandValue, (rand() % DustEffectRandValue) / CorrectionRandValue);

		// 値が大きすぎるので最後の補正をかけて速度に代入
		effectVelocity = randV * LastCorrection;
		effectVelocity.Normalize();

		if (dustEfectCount % TowFrequency == 0)
		{
			effectVelocity.x *= -1.0f;
			effectVelocity.z *= -1.0f;
		}

		if (dustEfectCount % ThreeFrequency == 0)
		{
			effectVelocity.y *= -1.0f;
		}

		//エフェクトを生成
		new DustEffect(this, effectPosition, effectVelocity);
	}
}

/*
@fn 破片エフェクト生産処理関数
*/
void BreakBlockObjectEffectManager::GenerateDebrisEffect()
{
	for (int i = 0; i < DebrisMaxEffect; i++)
	{
		// ランダムな値を生成
		Vector3 randDir((float)(rand() % DebrisEffectRandValue), (float)(rand() % DebrisEffectRandValue), 1.0f);
		randDir.Normalize();

		if (i % TowFrequency == 0)
		{
			randDir.x *= -1.0f;
		}

		if (i % ThreeFrequency == 0)
		{
			randDir.y *= -1.0f;
		}

		randDir.z = 1.0f;

		new DebrisEffectObject(effectPosition, randDir);
	}
}
