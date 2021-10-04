#include "TrackingEnemyStateAttack.h"

TrackingEnemyStateAttack::TrackingEnemyStateAttack()
	: AttcakMoveSpeed(100.0f)
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
		RotationProcess(_owner, trackingRotationVec, _owner->GetCharaForwardVec());
	}
	else
	{
		trackingRotationVec = trackingObject->GetPosition() - _owner->GetPosition();
		trackingRotationVec.z = 0.0f;
		trackingRotationVec.Normalize();
		velocity = trackingRotationVec * AttcakMoveSpeed;
		// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
		_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
		RotationProcess(_owner, trackingRotationVec, _owner->GetCharaForwardVec());
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

	firstPosition = _owner->GetFirstPosition();

	trackingObject = _owner->GetTrackingObject();
	moveSpeed = _owner->GetMoveSpeed();
	trackingRotationVec = trackingObject->GetPosition() - _owner->GetPosition();
	trackingRotationVec.z = 0.0f;
	trackingRotationVec.Normalize();

	RotationProcess(_owner, trackingRotationVec, _owner->GetCharaForwardVec());
}