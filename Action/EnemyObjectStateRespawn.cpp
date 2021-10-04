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
	// オーナーの今のポジションを取得
	nowPosition = _owner->GetPosition();
	// 今のポジションから初期ポジションへ向かう方向ベクトルを作成
	moveDirection = _owner->GetFirstPosition() - nowPosition;
	// 正規化
	moveDirection.Normalize();
	// 速度を計算ン
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
	_owner->SetIsAttack(false);
	// positionをリスポーンする場所にセット
	_owner->SetPosition(_owner->GetRespawnPosition());
}
