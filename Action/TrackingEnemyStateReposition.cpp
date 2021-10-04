#include "TrackingEnemyStateReposition.h"

TrackingEnemyStateReposition::TrackingEnemyStateReposition()
	: IdlingLength(2.0f)
{
}

TrackingEnemyStateReposition::~TrackingEnemyStateReposition()
{
}

EnemyState TrackingEnemyStateReposition::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// �ǐՃ^�[�Q�b�g�����Ȃ��ꍇ
	if (!_owner->GetIsTracking())
	{
		// ���|�W�V�����ϐ�
		Vector3 tmpPosition;
		// ���̃|�W�V�����Ə����|�W�V�����Ő��`��Ԃ����
		tmpPosition = Vector3::Lerp(_owner->GetPosition(), firstPosition, _deltaTime * 1.0);
		// �|�W�V�������Z�b�g
		_owner->SetPosition(tmpPosition);
	}
	else // ����ꍇ�ǐՏ�Ԃ�
	{
		state = EnemyState::ENEMY_STATE_TRACKING;
	}

	// ���̃|�W�V�������珉���|�W�V�����ւ̕����x�N�g�����v�Z
	repositionRotationVec = firstPosition - _owner->GetPosition();
	// �����ʒu�܂ł̒����𓾂邽�߂ɕϐ��֕ۑ�
	Vector3 chackReposition = repositionRotationVec;
	// ���K��
	repositionRotationVec.Normalize();
	// ��]����
	RotationProcess(_owner, repositionRotationVec, _owner->GetCharaForwardVec());

	// �������擾
	float Length = chackReposition.Length();

	// �������K��l�ȉ��̏ꍇ�A�C�h�����O��Ԃֈڍs
	if (Length <= IdlingLength)
	{
		state = EnemyState::ENEMY_STATE_IDLE;
	}

	return state;
}

void TrackingEnemyStateReposition::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_REPOSITION;
	_owner->SetState(State::Active);

	// �I�[�i�[�̈ړ����x�𓾂�
	moveSpeed = _owner->GetMoveSpeed();
	// �I�[�i�[�̏����|�W�V�����𓾂�
	firstPosition = _owner->GetFirstPosition();
	// ���̃|�W�V�������珉���|�W�V�����ւ̕����x�N�g�����v�Z
	repositionRotationVec = firstPosition - _owner->GetPosition();
	// ���K��
	repositionRotationVec.Normalize();

	// ��]����
	RotationProcess(_owner, repositionRotationVec, _owner->GetCharaForwardVec());
}
