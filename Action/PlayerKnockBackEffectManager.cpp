//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerKnockBackEffectManager.h"
#include "PlayerKnockBackEffect.h"
#include "PlayerObject.h"

/*
@fn コンストラクタ
@param	_owner 親クラスのポインタ
*/
PlayerKnockBackEffectManager::PlayerKnockBackEffectManager(PlayerObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, PositionOffset(150.0f)
	, DistanceOffset(30.0f)
{
	// メンバー変数の初期化	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	effectFrameCount = 0;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
PlayerKnockBackEffectManager::~PlayerKnockBackEffectManager()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void PlayerKnockBackEffectManager::UpdateGameObject(float _deltaTime)
{
	// 現在のステータスがノックバック状態だったらエフェクトを有効化
	if (owner->GetNowState() == PlayerState::PLAYER_STATE_KNOCKBACK)
	{
		// パーティクルを有効化
		particleState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		// パーティクルを無効化
		particleState = ParticleState::PARTICLE_DISABLE;
	}

	// ステータス状態を見る
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

/*
@fn エフェクトがアクティブ時の処理関数
*/
void PlayerKnockBackEffectManager::ActiveEffectProcess()
{
	++effectFrameCount;
	if (effectFrameCount % 5 == 0)
	{
		GenerateEffectProcess();
	}
}

/*
@fn エフェクト生産処理関数
*/
void PlayerKnockBackEffectManager::GenerateEffectProcess()
{
	// ownerのポジションを得る
	position = owner->GetPosition();
	position.z += PositionOffset;
	// オーナーの速度を得る
	distance = owner->GetVelocity();
	// 正規化
	distance.Normalize();
	// 速度を正規化したものに定数を掛ける
	distance *= DistanceOffset;
	//particleを生成
	new PlayerKnockBackEffect(owner, position, distance);
}