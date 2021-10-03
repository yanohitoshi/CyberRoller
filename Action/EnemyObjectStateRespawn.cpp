#include "EnemyObjectStateRespawn.h"

EnemyObjectStateRespawn::EnemyObjectStateRespawn()
	: moveDirection(Vector3::Zero)
	, nowPosition(Vector3::Zero)
	, RespawnMoveSpeed(200.0f)
{
}

EnemyObjectStateRespawn::~EnemyObjectStateRespawn()
{
}

EnemyState EnemyObjectStateRespawn::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	nowPosition = _owner->GetPosition();
	moveDirection = _owner->GetFirstPosition() - nowPosition;
	moveDirection.Normalize();
	velocity = moveDirection * RespawnMoveSpeed;
	// positionに速度を足してキャラクターを動かす
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// 現在のポジションが初期ポジション以下になったら
	// ※上から降りてくるため
	if (nowPosition.z <= _owner->GetFirstPosition().z)
	{
		state = EnemyState::ENEMY_STATE_IDLE;
	}

	return state;
}

void EnemyObjectStateRespawn::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// 描画をONに設定
	skeletalMeshComponent->SetVisible(true);
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_RESPAWN;
	// 死亡フラグをfalseにセット
	_owner->SetIsDeadFlag(false);
	// positionをリスポーンする場所にセット
	_owner->SetPosition(_owner->GetRespawnPosition());
}
