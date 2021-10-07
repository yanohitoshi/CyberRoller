//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "JumpAttackEffectManager.h"
#include "JumpAttackEffect.h"

/*
@fn コンストラクタ
@param	_owner 親クラスのポインタ
*/
JumpAttackEffectManager::JumpAttackEffectManager(GameObject* _owner)
	: GameObject(false, Tag::PARTICLE)
{
	// メンバー変数の初期化	
	owner = _owner;
	position = owner->GetPosition();
	effectPosition = Vector3::Zero;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
JumpAttackEffectManager::~JumpAttackEffectManager()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
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

/*
@fn エフェクトがアクティブ時の処理関数
*/
void JumpAttackEffectManager::ActiveEffectProcess()
{
	GenerateEffectProcess();
}

/*
@fn エフェクト生産処理関数
*/
void JumpAttackEffectManager::GenerateEffectProcess()
{
	// ownerのポジションを得る
	effectPosition = owner->GetPosition();
	// particleを生成
	new JumpAttackEffect(effectPosition, Vector3::Zero);
}
