//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerDeadEffectManager.h"
#include "PlayerDeadEffect.h"
#include "PlayerObject.h"

/*
@fn コンストラクタ
@param	_owner 親クラスのポインタ
*/
PlayerDeadEffectManager::PlayerDeadEffectManager(PlayerObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, PositionOffset(50.0f)
	, ShiftPositionZ(40.0f)
	, GenerationTime(30)
	, KnockBackOffset(30.0f)
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
PlayerDeadEffectManager::~PlayerDeadEffectManager()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void PlayerDeadEffectManager::UpdateGameObject(float _deltaTime)
{
	// 現在のステータスが死亡状態だったらエフェクトを有効化
	if (owner->GetNowState() == PlayerState::PLAYER_STATE_DEAD)
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
		generationCount = 0;
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
void PlayerDeadEffectManager::ActiveEffect()
{
	// 発生までの時間を数える
	++generationCount;

	// 時間が来たら発生開始
	if (generationCount >= GenerationTime)
	{
		// エフェクト発生開始後のカウントを数える
		++effectFrameCount;
		if (effectFrameCount % 5 == 0)
		{
			// 生成処理
			GenerateEffect();
		}
	}
}

/*
@fn エフェクト生産処理関数
*/
void PlayerDeadEffectManager::GenerateEffect()
{
	// ownerのポジションを得る
	position = owner->GetPosition();
	// オーナーの前方ベクトルの逆向きのベクトルを計算
	Vector3 direction = owner->GetCharaForwardVec() * -1.0f;
	// 計算したベクトルにオフセットを書ける
	position += direction * PositionOffset;
	// ｚ軸をずらす
	position.z += ShiftPositionZ;
	// オーナーの速度を得る
	distance = owner->GetVelocity();
	// 正規化
	distance.Normalize();
	// 速度を正規化したものに定数を掛ける
	distance *= KnockBackOffset;
	//particleを生成
	new PlayerDeadEffect(owner, position, distance);
}