#include "PlayerObjectStateFallDead.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateFallDead::PlayerObjectStateFallDead()
	: respawnTime(120)
{
}

PlayerObjectStateFallDead::~PlayerObjectStateFallDead()
{
}

PlayerState PlayerObjectStateFallDead::Update(PlayerObject* _owner, float _deltaTime)
{
	// 重力にデルタタイムをかけた値を代入
	velocity.z -= PlayerObject::GetGravity() * _deltaTime;

	// 落下速度が規定値を超えていたら
	if (velocity.z <= MaxFallSpeed)
	{
		// 規定値に固定
		velocity.z = MaxFallSpeed;
	}

	// 移動速度にデルタタイムを掛けてそれをポジションに追加して更新
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// リスポーンに移行するフラグがfalseだったら
	if (_owner->GetRespawnFlag() == false)
	{
		// 復帰までのカウント処理
		ToRespawnCountProcess(_owner);
	}

	if (_owner->GetRespawnFlag()) 	// リスポーンに移行するフラグがtrueだったら
	{
		// ステータスをリスポーンに変更する
		state = PlayerState::PLAYER_STATE_RESPAWN;
	}

	// 更新されたstateを返す
	return state;
}

void PlayerObjectStateFallDead::Input(PlayerObject* _owner, const InputState& _keyState)
{

}

void PlayerObjectStateFallDead::Enter(PlayerObject* _owner, float _deltaTime)
{

	// stateをFALL_DEAD状態にして保存
	state = PlayerState::PLAYER_STATE_FALL_DEAD;

	// リスポーンまでのカウントを初期化
	respawnCount = 0;

	// 入力可能フラグをfalseにセット
	_owner->SetIsAvailableInput(false);
}

void PlayerObjectStateFallDead::ToRespawnCountProcess(PlayerObject* _owner)
{
	// リスポーンするまでの時間をカウントする
	++respawnCount;
	// カウントが定数値に到達したら
	if (respawnCount >= respawnTime)
	{
		// リスポーンに移行するフラグをfalseに 
		_owner->SetRespawnFlag(true);
		// ownerにリスポーンするポジションを渡す
		_owner->SetPosition(_owner->GetRespownPos());
		// 死亡状態フラグをfalseに
		_owner->SetDeadFlag(false);
	}
}
