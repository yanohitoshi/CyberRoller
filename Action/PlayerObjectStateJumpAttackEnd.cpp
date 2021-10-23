//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateJumpAttackEnd.h"

/*
@fn コンストラクタ
*/
PlayerObjectStateJumpAttackEnd::PlayerObjectStateJumpAttackEnd()
	: SuccessJumpTime(6)
	, SuccessJumpAccelPower(80.0f)
	, JumpAttackSuccessFirstPower(1500.0f)
{
}

/*
@fn デストラクタ
*/
PlayerObjectStateJumpAttackEnd::~PlayerObjectStateJumpAttackEnd()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
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
	if (endFlag == true || !_owner->GetIsJumpAttackSuccess())
	{
		// owner変数を更新
		_owner->SetMoveSpeed(moveSpeed);
		_owner->SetVelocity(velocity);
		_owner->SetIsJumpAttackSuccess(false);
		_owner->SetIsJumpAttck(false);

		// ステータスをジャンプループにする
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

	CheckDeadFlag(_owner);

	CheckTimeOverFlag();

    return state;
}

/*
@fn インプット
@brief	stateに応じて入力処理を行う
@param	_owner 親クラスのポインタ
@param	_keyState 入力情報
*/
void PlayerObjectStateJumpAttackEnd::Input(PlayerObject* _owner, const InputState& _keyState)
{
	if (_owner->GetIsJumpAttackSuccess())
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
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void PlayerObjectStateJumpAttackEnd::Enter(PlayerObject* _owner, float _deltaTime)
{
    // stateをジャンプ攻撃状態にして保存
    state = PlayerState::PLAYER_STATE_JUMP_ATTACK_END;
	endFlag = false;
	jumpFrameCount = 0;

	// ジャンプ攻撃が成功したかどうか判定
	if (_owner->GetIsJumpAttackSuccess())
	{
		// ジャンプ力をセットする
		_owner->SetJumpPower(JumpAttackSuccessFirstPower);
		_owner->SetIsAvailableJumpAttck(true);
	}
	else
	{
		moveSpeed = _owner->GetMoveSpeed() * 0.5f;
		velocity = _owner->GetVelocity();
		velocity.z = 0.0f;
		_owner->SetVelocity(velocity);
	}
}
