//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectStateTurn.h"

/*
@fn �R���X�g���N�^
*/
EnemyObjectStateTurn::EnemyObjectStateTurn()
{
}

/*
@fn �f�X�g���N�^
*/
EnemyObjectStateTurn::~EnemyObjectStateTurn()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
EnemyState EnemyObjectStateTurn::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// �A�j���[�V�����̍Đ����I����Ă�����
	if (!skeletalMeshComponent->IsPlaying())
	{
		// �X�e�[�^�X��ҋ@��Ԃɂ���
		state = EnemyState::ENEMY_STATE_REPOSITION;
	}

	if (_owner->GetIsDead())
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
void EnemyObjectStateTurn::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_TURN));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_TURN;
	// �X�e�[�^�X��Active��set
	_owner->SetState(State::Active);
}
