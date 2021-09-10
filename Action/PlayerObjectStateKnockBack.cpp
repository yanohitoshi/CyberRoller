//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateKnockBack.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateKnockBack::PlayerObjectStateKnockBack()
{
}

PlayerObjectStateKnockBack::~PlayerObjectStateKnockBack()
{
}

PlayerState PlayerObjectStateKnockBack::Update(PlayerObject* _owner, float _deltaTime)
{
	if (!_owner->GetOnGround())
	{
		// 重力にデルタタイムをかけた値を代入
		velocity.z -= PlayerObject::GetGravity() * _deltaTime;
		velocity += knockBackDirection * 10.0f;
		velocity.z += 50.0f;

		// 接地したら
		if (_owner->GetOnGround())
		{
			velocity.x = 0.0f;
			velocity.y = 0.0f;
			_owner->SetVelocity(velocity);
			// 壁に当たったフラグをfalseに
			_owner->SetIsHitEnemy(false);
			// stateをアイドリングに変更
			state = PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE;
		}
	}
	else
	{
		velocity += knockBackDirection * 25.0f;

		if (!skeletalMeshComponent->IsPlaying())
		{
			velocity.x = 0.0f;
			velocity.y = 0.0f;
			_owner->SetVelocity(velocity);
			// 壁に当たったフラグをfalseに
			_owner->SetIsHitEnemy(false);
			// stateをアイドリングに変更
			state = PlayerState::PLAYER_STATE_IDLE;
		}

	}

	// 移動速度にデルタタイムを掛けてそれをポジションに追加して更新
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
	_owner->SetVelocity(velocity);
	

	//else if (!skeletalMeshComponent->IsPlaying() && !_owner->GetOnGround())
	//{
	//	_owner->SetVelocity(velocity);
	//	// 壁に当たったフラグをfalseに
	//	_owner->SetIsHitEnemy(false);
	//	// stateをアイドリングに変更
	//	state = PlayerState::PLAYER_STATE_JUMPLOOP;
	//}

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
	//// 移動ベクトルを0.0fに設定
	//_owner->SetVelocity(Vector3::Zero);

	hitEnemyPosition = _owner->GetHitEnemyPosition();
	knockBackDirection = _owner->GetPosition() - hitEnemyPosition;
	knockBackDirection.z = 0.0f;
	knockBackDirection.Normalize();

	RotationProcess(_owner, knockBackDirection * -1.0f,_owner->GetCharaForwardVec());

	if (!_owner->GetOnGround())
	{
    	velocity.z = 500.0f;
	}
}