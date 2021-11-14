#include "EnhancedEnemyStateFlinch.h"

EnhancedEnemyStateFlinch::EnhancedEnemyStateFlinch()
	: EndTime(60)
	, FirstBlowAwayPower(100.0f)
	, BlowAwayPower(1.2f)
	, MaxSpeed(500.0f)
{
}

EnhancedEnemyStateFlinch::~EnhancedEnemyStateFlinch()
{
}

EnemyState EnhancedEnemyStateFlinch::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	++flinchCount;

	// �����x
	moveSpeed *= BlowAwayPower;

	// �ő呬�x�ɓ��B���Ă�����ő呬�x�ɌŒ肷��
	if (moveSpeed >= MaxSpeed)
	{
		moveSpeed = MaxSpeed;
	}

	// ��p���鑬�x�x�N�g���v�Z
	velocity = blowAwayDirection * moveSpeed;

	// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// ���Ԃ������烊�X�|�[��
	if (flinchCount >= EndTime)
	{
		_owner->SetIsFlinch(false);
		state = EnemyState::ENEMY_STATE_IDLE;
	}

	return state;
}

void EnhancedEnemyStateFlinch::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_FLINCH));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_FLINCH;
	_owner->SetState(State::Disabling);

	// �J�E���g������
	flinchCount = 0;
	// ������ԕ������v�Z
	blowAwayDirection = _owner->GetPosition() - _owner->GetDefeatedObjectPosition();
	// ���K��
	blowAwayDirection.Normalize();
	// �㉺������0�ɌŒ�
	blowAwayDirection.z = 0.0f;
	// �ړ����x�������ɂ���
	moveSpeed = FirstBlowAwayPower;
}
