//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "MoveEnemyObjectStateMoving.h"

/*
@fn �R���X�g���N�^
*/
MoveEnemyObjectStateMoving::MoveEnemyObjectStateMoving()
{
}

/*
@fn �f�X�g���N�^
*/
MoveEnemyObjectStateMoving::~MoveEnemyObjectStateMoving()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
EnemyState MoveEnemyObjectStateMoving::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// �ړ�����
	Move(_owner, _deltaTime);

	// �ړ�Tag�𔻕ʂ��ĐU��Ԃ�ꏊ�ɓ��B���Ă��邩����
	if (_owner->GetMoveEnemyTag() == MoveEnemyTag::RIGHT_MOVE)
	{
		if (_owner->GetPosition().y > firstPosition.y + moveDistance && moveDistance > 0.0f)
		{
			state = EnemyState::ENEMY_STATE_TURN;
		}

		if (_owner->GetPosition().y < firstPosition.y + moveDistance && moveDistance < 0.0f)
		{
			state = EnemyState::ENEMY_STATE_TURN;
		}
	}
	else if (_owner->GetMoveEnemyTag() == MoveEnemyTag::LEFT_MOVE)
	{
		if (_owner->GetPosition().y < firstPosition.y - moveDistance && moveDistance > 0.0f)
		{
			state = EnemyState::ENEMY_STATE_TURN;
		}

		if (_owner->GetPosition().y > firstPosition.y - moveDistance && moveDistance < 0.0f)
		{
			state = EnemyState::ENEMY_STATE_TURN;
		}
	}

	// ���S���Ă�����
	if (_owner->GetIsDeadFlag())
	{
		state = EnemyState::ENEMY_STATE_DEAD;
	}

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void MoveEnemyObjectStateMoving::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_MOVING;
	_owner->SetState(State::Active);

	moveDirection = _owner->GetMoveDirection();
	moveDistance = _owner->GetMoveDistance();
	moveSpeed = _owner->GetMoveSpeed();
	firstPosition = _owner->GetFirstPosition();

	RotationProcess(_owner, moveDirection, _owner->GetCharaForwardVec());
}

/*
@fn �ړ������֐�
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void MoveEnemyObjectStateMoving::Move(EnemyObjectBase* _owner, float _deltaTime)
{
	velocity = moveDirection * moveSpeed;
		
	// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
}
