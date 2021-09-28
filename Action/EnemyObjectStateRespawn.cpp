#include "EnemyObjectStateRespawn.h"

EnemyObjectStateRespawn::EnemyObjectStateRespawn()
	: nowScale(Vector3::Zero)
{
}

EnemyObjectStateRespawn::~EnemyObjectStateRespawn()
{
}

EnemyState EnemyObjectStateRespawn::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	nowScale += Vector3(0.01f, 0.01f, 0.01f);
	_owner->SetScale(nowScale);

	if (nowScale.x >= 2.0f)
	{
		_owner->SetScale(Vector3(2.0f, 2.0f, 2.0f));
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
	_owner->SetScale(Vector3::Zero);
	// 現在のscale値を取得
	nowScale = Vector3::Zero;
	// 死亡フラグをfalseにセット
	_owner->SetIsDeadFlag(false);
	// positionを初期位置に直す
	_owner->SetPosition(_owner->GetFirstPosition());
}
