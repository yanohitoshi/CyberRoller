//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnhancedEnemyStateIdle.h"

/*
@fn �R���X�g���N�^
*/
EnhancedEnemyStateIdle::EnhancedEnemyStateIdle()
	: StayTime(40)
{
}

/*
@fn �f�X�g���N�^
*/
EnhancedEnemyStateIdle::~EnhancedEnemyStateIdle()
{

}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return EnemyState ���̃X�e�[�^�X
*/
EnemyState EnhancedEnemyStateIdle::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	++frameCount;
	// �ǐՊJ�n�����𔻒�
	bool isStartTracking = _owner->GetIsTracking() && !_owner->GetIsDead() && frameCount > StayTime;

	// �����𖞂����Ă�����
	if (isStartTracking)
	{
		// �ǐՏ�ԂɑJ��
		state = EnemyState::ENEMY_STATE_TRACKING;
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
void EnhancedEnemyStateIdle::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_IDLE;
	// �X�e�[�^�X��L����
	_owner->SetState(State::Active);
	frameCount = 0;
}