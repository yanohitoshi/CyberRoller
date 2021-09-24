#include "TrackingEnemyStateTurn.h"

TrackingEnemyStateTurn::TrackingEnemyStateTurn()
{
}

TrackingEnemyStateTurn::~TrackingEnemyStateTurn()
{
}

EnemyState TrackingEnemyStateTurn::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// �A�j���[�V�����̍Đ����I����Ă�����
	if (!skeletalMeshComponent->IsPlaying())
	{
		// �X�e�[�^�X��ҋ@��Ԃɂ���
		state = EnemyState::ENEMY_STATE_REPOSITION;
	}

	if (_owner->GetIsDeadFlag())
	{
		state = EnemyState::ENEMY_STATE_DEAD;
	}

	return state;
}

void TrackingEnemyStateTurn::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_TURN));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_TURN;
	_owner->SetState(State::Active);
}
