#include "TrackingEnemyStateReposition.h"

TrackingEnemyStateReposition::TrackingEnemyStateReposition()
{
}

TrackingEnemyStateReposition::~TrackingEnemyStateReposition()
{
}

EnemyState TrackingEnemyStateReposition::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	//repositionRotationVec = _owner->GetPosition() - firstPosition;
	//repositionRotationVec.Normalize();

	if (!_owner->GetIsTracking())
	{
		velocity = repositionRotationVec * moveSpeed;
		// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
		_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
	}
	else
	{
		state = EnemyState::ENEMY_STATE_TRACKING;
	}

	return state;
	//RotationProcess(_owner, repositionRotationVec, _owner->GetCharaForwardVec());
}

void TrackingEnemyStateReposition::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_TRACKING;
	_owner->SetState(State::Active);

	moveSpeed = _owner->GetMoveSpeed();
	firstPosition = _owner->GetFirstPosition();
	repositionRotationVec = _owner->GetPosition() - firstPosition;
	repositionRotationVec.Normalize();

	RotationProcess(_owner, repositionRotationVec, _owner->GetCharaForwardVec());
}
