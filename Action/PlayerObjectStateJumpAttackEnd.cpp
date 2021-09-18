#include "PlayerObjectStateJumpAttackEnd.h"

PlayerObjectStateJumpAttackEnd::PlayerObjectStateJumpAttackEnd()
	: SuccessJumpTime(6)
	, SuccessJumpAccelPower(80.0f)
	, JumpAttackSuccessFirstPower(1500.0f)
{
}

PlayerObjectStateJumpAttackEnd::~PlayerObjectStateJumpAttackEnd()
{
}

PlayerState PlayerObjectStateJumpAttackEnd::Update(PlayerObject* _owner, float _deltaTime)
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
	// state終了フラグがtrueになっていたら
	if (endFlag == true)
	{
		// owner変数を更新
		_owner->SetMoveSpeed(moveSpeed);
		_owner->SetVelocity(velocity);
		_owner->SetJumpFrameCount(jumpFrameCount);
		_owner->SetIsJumpAttackSuccess(false);
		_owner->SetIsJumpAttck(false);

		// ステータスをジャンプループにする
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

    return state;
}

void PlayerObjectStateJumpAttackEnd::Input(PlayerObject* _owner, const InputState& _keyState)
{

	// ジャンプしている時間をフレームでカウント
	++jumpFrameCount;

	// ジャンプ力の仮変数を作り前フレームでのジャンプ力をもらう
	float jumpPower = _owner->GetJumpPower();

	// Z軸にジャンプ力を代入
	velocity.z = jumpPower;

	// スイッチジャンプでかつジャンプ利用可能な時間内だったら
	if (SuccessJumpTime > jumpFrameCount)
	{
		// ジャンプ力に定数値を足してジャンプ力をownerのジャンプ力変数にセット
		_owner->SetJumpPower(jumpPower + SuccessJumpAccelPower);
	}
	else // ジャンプ利用時間を経過していたら
	{
		// ステータス終了フラグをtrueにセット
		endFlag = true;
	}
}

void PlayerObjectStateJumpAttackEnd::Enter(PlayerObject* _owner, float _deltaTime)
{
    // stateをジャンプ攻撃状態にして保存
    state = PlayerState::PLAYER_STATE_JUMP_ATTACK_END;
	endFlag = false;
	jumpFrameCount = 0;
	// ジャンプ力をセットする
	_owner->SetJumpPower(JumpAttackSuccessFirstPower);

	if (_owner->GetIsSelectingTargetEnemy())
	{
		_owner->SetIsAvailableJumpAttck(true);
	}
}
