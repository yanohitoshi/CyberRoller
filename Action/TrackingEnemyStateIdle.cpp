//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TrackingEnemyStateIdle.h"

/*
@fn �R���X�g���N�^
*/
TrackingEnemyStateIdle::TrackingEnemyStateIdle()
	: StayTime(60)
{
}

/*
@fn �f�X�g���N�^
*/
TrackingEnemyStateIdle::~TrackingEnemyStateIdle()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
EnemyState TrackingEnemyStateIdle::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	++frameCount;
	// �ǐՊJ�n�̏�����������Ă��邩
	bool isStartTracking = _owner->GetIsTracking() && !_owner->GetIsDead() && frameCount > StayTime;
	// �ǐՊJ�n�̏�����������Ă�����
	if (isStartTracking)
	{
		// �ǐՏ�Ԃ֑J��
		state = EnemyState::ENEMY_STATE_TRACKING;
	}

	// ��������ł�����
	if (_owner->GetIsDead())
	{
		// ���S��Ԃ֑J��
		state = EnemyState::ENEMY_STATE_DEAD;
	}

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void TrackingEnemyStateIdle::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_IDLE;
	// �X�e�[�^�X��L����
	_owner->SetState(State::Active);
	// �ϐ�������
	frameCount = 0;
}