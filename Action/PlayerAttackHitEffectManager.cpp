//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerAttackHitEffectManager.h"
#include "PlayerAttackHitEffect.h"
#include "PlayerObject.h"

/*
@fn コンストラクタ
@param	_owner 親クラスのポインタ
*/
PlayerAttackHitEffectManager::PlayerAttackHitEffectManager(PlayerObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, CorrectionPosition(100.0f)
{
	// メンバー変数の初期化	
	owner = _owner;
	position = owner->GetPosition();
	generateFlag = true;
	velocity = Vector3::Zero;
	effectPosition = Vector3::Zero;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
PlayerAttackHitEffectManager::~PlayerAttackHitEffectManager()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void PlayerAttackHitEffectManager::UpdateGameObject(float _deltaTime)
{
	// 親クラスのステータスがActiveだったら
	if (owner->GetIsJumpAttackSuccess())
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

/*
@fn エフェクトがアクティブ時の処理関数
*/
void PlayerAttackHitEffectManager::ActiveEffectProcess()
{
	// 生成フラグがtrueだったら
	if (generateFlag == true)
	{
		// エフェクト生産関数
		GenerateEffectProcess();
		generateFlag = false;
	}
}

/*
@fn エフェクト生産処理関数
*/
void PlayerAttackHitEffectManager::GenerateEffectProcess()
{
	// ポジション計算
	effectPosition = owner->GetPosition() + owner->GetForwardVec() * CorrectionPosition;
	// エフェクト生成
	new PlayerAttackHitEffect(owner, effectPosition, velocity);
}