#include "NormalEnemyObjectStateIdle.h"

NormalEnemyObjectStateIdle::NormalEnemyObjectStateIdle()
{
}

NormalEnemyObjectStateIdle::~NormalEnemyObjectStateIdle()
{
}

EnemyState NormalEnemyObjectStateIdle::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	if (_owner->GetIsDeadFlag())
	{
		state = EnemyState::ENEMY_STATE_DEAD;
	}

	return state;
}

void NormalEnemyObjectStateIdle::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_IDLE;
	_owner->SetState(State::Active);
}
