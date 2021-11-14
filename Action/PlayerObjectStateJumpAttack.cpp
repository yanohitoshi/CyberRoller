//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateJumpAttack.h"
#include "SkeletalMeshComponent.h"

/*
@fn コンストラクタ
*/
PlayerObjectStateJumpAttack::PlayerObjectStateJumpAttack()
	: AttackSpeed(3000.0f)
	, UnSelectTargetAttackTime(15)
{
}

/*
@fn デストラクタ
*/
PlayerObjectStateJumpAttack::~PlayerObjectStateJumpAttack()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
PlayerState PlayerObjectStateJumpAttack::Update(PlayerObject* _owner, float _deltaTime)
{
	// ターゲットを捉えていてかつターゲットがActiveだったら
	if (isSelectingTargetEnemy && attackTarget->GetState() == State::Active)
	{
		// 仮ポジション変数
		Vector3 tmpPosition;
		// 線形補完をとり変数に保存
		tmpPosition = Vector3::Lerp(_owner->GetPosition(), attackTarget->GetPosition(), _deltaTime * 9.0);
		// ポジションをセット
		_owner->SetPosition(tmpPosition);
	}
	else // ターゲットがいない場合のジャンプアタック移動処理
	{
		++unSelectTargetEnemyFrameCount;
		jumpAttackDirection.z = 0.0f;
		velocity = jumpAttackDirection * AttackSpeed;
		_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
	} 


	// ジャンプアタック成功またはジャンプアタックの時間が終了していたらステータスを変更
	if (_owner->GetIsJumpAttackSuccess() || unSelectTargetEnemyFrameCount > UnSelectTargetAttackTime)
	{
		_owner->SetMoveSpeed(AttackSpeed);
		state = PlayerState::PLAYER_STATE_JUMP_ATTACK_END;
	}

	CheckDeadFlag(_owner);

	CheckTimeOverFlag();

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void PlayerObjectStateJumpAttack::Enter(PlayerObject* _owner, float _deltaTime)
{
	// stateをジャンプ攻撃状態にして保存
	state = PlayerState::PLAYER_STATE_JUMP_ATTACK;
	unSelectTargetEnemyFrameCount = 0;

	// 一度ジャンプ攻撃使用不可にセット
	_owner->SetIsAvailableJumpAttck(false);

	isSelectingTargetEnemy = _owner->GetIsSelectingTargetObject();
	// ターゲットを捉えているか判定
	if (isSelectingTargetEnemy && _owner->GetAttackTargetEnemy()->GetState() == State::Active)
	{
		attackTarget = _owner->GetAttackTargetEnemy();
	}
	else
	{
		jumpAttackDirection = _owner->GetCharaForwardVec();
	}
}
