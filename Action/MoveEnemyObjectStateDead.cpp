#include "MoveEnemyObjectStateDead.h"


MoveEnemyObjectStateDead::MoveEnemyObjectStateDead()
{
}

MoveEnemyObjectStateDead::~MoveEnemyObjectStateDead()
{
}

EnemyState MoveEnemyObjectStateDead::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	++frameCount;

	if (frameCount >= 300)
	{
		_owner->SetIsDeadFlag(false);
		state = EnemyState::ENEMY_STATE_IDLE;
	}

	return state;
}

void MoveEnemyObjectStateDead::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_DEAD));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_DEAD;

	_owner->SetState(State::Disabling);

	frameCount = 0;
}