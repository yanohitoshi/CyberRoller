//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerSandSmokeMakeManager.h"
#include "PlayerSandSmokeEffect.h"
#include "PlayerObject.h"

PlayerSandSmokeMakeManager::PlayerSandSmokeMakeManager(PlayerObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, GenerateSpeedValue(600.0f)
	, ShiftPositionValue(30.0f)
{
	// メンバー変数の初期化	
	owner = _owner;
	position = owner->GetPosition();
	frameCount = 0;
	generateCount = 0;
	effectPosition = Vector3::Zero;
	ownerState = owner->GetNowState();
}

PlayerSandSmokeMakeManager::~PlayerSandSmokeMakeManager()
{
}

void PlayerSandSmokeMakeManager::UpdateGameObject(float _deltaTime)
{
	ownerState = owner->GetNowState();

	// ownerの速度を参照して有効か無効を判定
	// 地面に接地中でｘもしくはｙの速度が0でなければ
	if (ownerState == PlayerState::PLAYER_STATE_RUN || ownerState == PlayerState::PLAYER_STATE_RUN_START)
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
		// 初期化
		generateCount = 0;
		break;

		// 有効状態だったら
	case PARTICLE_ACTIVE:

		ActiveEffectProcess();

		break;
	}

}

void PlayerSandSmokeMakeManager::ActiveEffectProcess()
{
	// ownerのポジションを得る
	position = owner->GetPosition();

	// フレームカウントを数える
	++frameCount;

	// 10フレームに1度プレイヤーの移動速度が一定以上だったら
	if (frameCount % 10 == 0 && owner->GetVelocity().x > GenerateSpeedValue ||
		frameCount % 10 == 0 && owner->GetVelocity().y > GenerateSpeedValue ||
		frameCount % 10 == 0 && owner->GetVelocity().x < -GenerateSpeedValue||
		frameCount % 10 == 0 && owner->GetVelocity().y < -GenerateSpeedValue )
	{
		GenerateEffectProcess();
	}


}

void PlayerSandSmokeMakeManager::GenerateEffectProcess()
{
	// 生成した数を数える
	++generateCount;

	// カウントが2の倍数の時は右足に
	if (generateCount % 2 == 0)
	{
		ShiftRightEffectPosition();
	}
	else
	{
		ShiftLeftEffectPosition();
	}

	// オーナーの速度をもらう
	Vector3 vel = owner->GetVelocity();

	// 正規化
	vel.Normalize();

	// 速度を逆向きにする
	vel = vel * -1.0f;

	// particleを生成
	new PlayerSandSmokeEffect(effectPosition, vel);
}

void PlayerSandSmokeMakeManager::ShiftRightEffectPosition()
{
	// 一度positionを保存
	effectPosition = position;

	// エフェクトのポジションをずらし足から出ているように見せる
	if (owner->GetVelocity().x > 1.0f)
	{
		effectPosition.y += ShiftPositionValue;
	}
	else if (owner->GetVelocity().x < -1.0f)
	{
		effectPosition.y -= ShiftPositionValue;
	}
	else if (owner->GetVelocity().y > 1.0f)
	{
		effectPosition.x += ShiftPositionValue;
	}
	else if (owner->GetVelocity().y < -1.0f)
	{
		effectPosition.x -= ShiftPositionValue;
	}

}

void PlayerSandSmokeMakeManager::ShiftLeftEffectPosition()
{
	// 一度positionを保存
	effectPosition = position;

	// エフェクトのポジションをずらし足から出ているように見せる
	if (owner->GetVelocity().x > 1.0f)
	{
		effectPosition.y -= ShiftPositionValue;
	}
	else if (owner->GetVelocity().x < -1.0f)
	{
		effectPosition.y += ShiftPositionValue;
	}
	else if (owner->GetVelocity().y > 1.0f)
	{
		effectPosition.x -= ShiftPositionValue;
	}
	else if (owner->GetVelocity().y < -1.0f)
	{
		effectPosition.x += ShiftPositionValue;
	}
}
