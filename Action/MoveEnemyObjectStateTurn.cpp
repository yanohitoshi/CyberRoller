//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "MoveEnemyObjectStateTurn.h"

/*
@fn �R���X�g���N�^
*/
MoveEnemyObjectStateTurn::MoveEnemyObjectStateTurn()
{
}

/*
@fn �f�X�g���N�^
*/
MoveEnemyObjectStateTurn::~MoveEnemyObjectStateTurn()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
EnemyState MoveEnemyObjectStateTurn::Update(EnemyObjectBase* _owner, float _deltaTime)
{

	// �A�j���[�V�����̍Đ����I����Ă�����
	if (!skeletalMeshComponent->IsPlaying())
	{
		_owner->SetMoveDirection(_owner->GetMoveDirection() * -1.0f);
		_owner->SetMoveDistance(_owner->GetMoveDistance() * -1.0f);
		// �X�e�[�^�X��ҋ@��Ԃɂ���
		state = EnemyState::ENEMY_STATE_MOVING;
	}

	// ���S��Ԃ�����
	if (_owner->GetIsDead())
	{
		// ���S��ԂɑJ��
		state = EnemyState::ENEMY_STATE_DEAD;
	}

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void MoveEnemyObjectStateTurn::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_TURN));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_TURN;
	_owner->SetState(State::Active);
}