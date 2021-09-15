#include "EnemyObjectStateDead.h"

EnemyObjectStateDead::EnemyObjectStateDead()
{
}

EnemyObjectStateDead::~EnemyObjectStateDead()
{
}

EnemyState EnemyObjectStateDead::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	return state;
}

void EnemyObjectStateDead::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_DEAD));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_DEAD;
}