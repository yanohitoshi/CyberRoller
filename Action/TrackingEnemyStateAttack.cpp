//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TrackingEnemyStateAttack.h"

/*
@fn コンストラクタ
*/
TrackingEnemyStateAttack::TrackingEnemyStateAttack()
	: AttcakMoveSpeed(100.0f)
{
}

/*
@fn デストラクタ
*/
TrackingEnemyStateAttack::~TrackingEnemyStateAttack()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
EnemyState TrackingEnemyStateAttack::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// アニメーションの再生が終わっていたら
	if (!skeletalMeshComponent->IsPlaying())
	{
		_owner->SetIsAttack(false);
		state = EnemyState::ENEMY_STATE_IDLE;
		RotationProcess(_owner, trackingRotationVec, _owner->GetCharaForwardVec());
	}
	else
	{
		trackingRotationVec = trackingObject->GetPosition() - _owner->GetPosition();
		trackingRotationVec.z = 0.0f;
		trackingRotationVec.Normalize();
		velocity = trackingRotationVec * AttcakMoveSpeed;
		// positionに速度を足してキャラクターを動かす
		_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
		RotationProcess(_owner, trackingRotationVec, _owner->GetCharaForwardVec());
	}

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void TrackingEnemyStateAttack::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_ATTACK));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_ATTACK;

	_owner->SetState(State::Active);

	firstPosition = _owner->GetFirstPosition();

	trackingObject = _owner->GetTrackingObject();
	moveSpeed = _owner->GetMoveSpeed();
	trackingRotationVec = trackingObject->GetPosition() - _owner->GetPosition();
	trackingRotationVec.z = 0.0f;
	trackingRotationVec.Normalize();

	RotationProcess(_owner, trackingRotationVec, _owner->GetCharaForwardVec());
}