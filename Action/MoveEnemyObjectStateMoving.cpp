#include "MoveEnemyObjectStateMoving.h"


MoveEnemyObjectStateMoving::MoveEnemyObjectStateMoving()
{
}

MoveEnemyObjectStateMoving::~MoveEnemyObjectStateMoving()
{
}

EnemyState MoveEnemyObjectStateMoving::Update(EnemyObjectBase* _owner, float _deltaTime)
{

	Move(_owner, _deltaTime);


	if (_owner->GetPosition().y > firstPosition.y + moveDistance && moveDistance > 0.0f)
	{
		state = EnemyState::ENEMY_STATE_TURN;
	}

	if (_owner->GetPosition().y < firstPosition.y + moveDistance && moveDistance < 0.0f)
	{
		state = EnemyState::ENEMY_STATE_TURN;
	}

	if (_owner->GetIsDeadFlag())
	{
		state = EnemyState::ENEMY_STATE_DEAD;
	}

	return state;
}

void MoveEnemyObjectStateMoving::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_MOVING;
	_owner->SetState(State::Active);

	moveDirection = _owner->GetMoveDirection();
	moveDistance = _owner->GetMoveDistance();
	moveSpeed = _owner->GetMoveSpeed();
	firstPosition = _owner->GetFirstPosition();

	RotationProcess(_owner, moveDirection, _owner->GetCharaForwardVec());
}

void MoveEnemyObjectStateMoving::Move(EnemyObjectBase* _owner, float _deltaTime)
{
	
	velocity = moveDirection * moveSpeed;
		
	// positionに速度を足してキャラクターを動かす
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
}
