#include "TrackingEnemyStateAttack.h"

TrackingEnemyStateAttack::TrackingEnemyStateAttack()
{
}

TrackingEnemyStateAttack::~TrackingEnemyStateAttack()
{
}

EnemyState TrackingEnemyStateAttack::Update(EnemyObjectBase* _owner, float _deltaTime)
{

	// �A�j���[�V�����̍Đ����I����Ă�����
	if (!skeletalMeshComponent->IsPlaying())
	{
		_owner->SetIsAttack(false);
		state = EnemyState::ENEMY_STATE_IDLE;
	}

	return state;
}

void TrackingEnemyStateAttack::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_ATTACK));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_ATTACK;

	_owner->SetState(State::Active);
}