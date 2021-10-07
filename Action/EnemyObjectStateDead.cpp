//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectStateDead.h"

/*
@fn �R���X�g���N�^
*/
EnemyObjectStateDead::EnemyObjectStateDead()
	: RespawnTime(120)
{
}

/*
@fn �f�X�g���N�^
*/
EnemyObjectStateDead::~EnemyObjectStateDead()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
EnemyState EnemyObjectStateDead::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	++frameCount;

	// ���Ԃ������烊�X�|�[��
	if (frameCount >= RespawnTime)
	{
		skeletalMeshComponent->SetVisible(false);
		state = EnemyState::ENEMY_STATE_RESPAWN;
	}

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void EnemyObjectStateDead::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_DEAD));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_DEAD;
	_owner->SetState(State::Disabling);
	frameCount = 0;
}
