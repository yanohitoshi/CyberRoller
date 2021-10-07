//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateKnockBack.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateKnockBack::PlayerObjectStateKnockBack()
	: knockBackFrameCount(0)
	, KnockBackSpeed(70.0f)
	, KnockBackTime(22)
{
}

PlayerObjectStateKnockBack::~PlayerObjectStateKnockBack()
{
}

PlayerState PlayerObjectStateKnockBack::Update(PlayerObject* _owner, float _deltaTime)
{
	// ノックバックの時間を数える
	++knockBackFrameCount;

	// 速度を追加
	velocity += knockBackDirection * KnockBackSpeed;

	// 接地中か判定
	if (!_owner->GetOnGround())
	{
		// 重力をかける
		velocity.z -= PlayerObject::GetGravity() * _deltaTime;
	}
	else
	{
		velocity.z = 0.0f;
	}

	// ノックバック時間を過ぎたら
	if (knockBackFrameCount >= KnockBackTime)
	{
		velocity.Zero;
		_owner->SetVelocity(velocity);
		// 壁に当たったフラグをfalseに
		_owner->SetIsHitEnemy(false);
		// stateをアイドリングに変更
		state = PlayerState::PLAYER_STATE_IDLE;
	}

	// 移動速度にデルタタイムを掛けてそれをポジションに追加して更新
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
	_owner->SetVelocity(velocity);
	
	ChackDeadFlag(_owner);

	ChackTimeOverFlag();

	// 更新されたstateを返す
	return state;
}

void PlayerObjectStateKnockBack::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateKnockBack::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_KNOCKBACK));
	// stateを怯み状態にして保存
	state = PlayerState::PLAYER_STATE_KNOCKBACK;

	// 速度初期化
	velocity = Vector3::Zero;
	// カウントを初期化
	knockBackFrameCount = 0;

	// 当たったエネミーのポジションを取得
	hitEnemyPosition = _owner->GetHitEnemyPosition();
	// ノックバックする方向ベクトルを計算
	knockBackDirection = _owner->GetPosition() - hitEnemyPosition;
	// 正規化
	knockBackDirection.Normalize();

	// 回転処理
	// ノックバック時動く方向と逆の方向を向かせるのでx,y軸に-1.0をかける
	RotationProcess(_owner,Vector3(knockBackDirection.x * -1.0f, knockBackDirection.y * -1.0f,0.0f) ,_owner->GetCharaForwardVec());
}