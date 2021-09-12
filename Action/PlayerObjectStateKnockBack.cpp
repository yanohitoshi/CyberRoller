//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateKnockBack.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateKnockBack::PlayerObjectStateKnockBack()
	: knockBackFrameCount(0)
{
}

PlayerObjectStateKnockBack::~PlayerObjectStateKnockBack()
{
}

PlayerState PlayerObjectStateKnockBack::Update(PlayerObject* _owner, float _deltaTime)
{

	++knockBackFrameCount;

	if (!_owner->GetOnGround())
	{
		// 重力にデルタタイムをかけた値を代入
		velocity.z -= PlayerObject::GetGravity() * _deltaTime;
	}

	velocity += knockBackDirection * 50.0f;

	velocity.z = 0.0f;
	if (knockBackFrameCount >= 22 )
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
	
	// 死亡フラグが立っていたら
	if (_owner->GetDeadFlag())
	{
		state = PlayerState::PLAYER_STATE_DEAD;
	}

	// タイムオーバーフラグがtrueだったら
	if (CountDownFont::GetTimeOverFlag() == true)
	{
		// ステータスをコンティニュー選択開始状態にする
		state = PlayerState::PLAYER_STATE_DOWNSTART;
	}

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

	velocity = Vector3::Zero;

	knockBackFrameCount = 0;

	hitEnemyPosition = _owner->GetHitEnemyPosition();
	knockBackDirection = _owner->GetPosition() - hitEnemyPosition;

	knockBackDirection.Normalize();

	RotationProcess(_owner,Vector3(knockBackDirection.x * -1.0f, knockBackDirection.y * -1.0f,0.0f) ,_owner->GetCharaForwardVec());


}