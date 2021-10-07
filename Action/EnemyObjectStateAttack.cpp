//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectStateAttack.h"

/*
@fn �R���X�g���N�^
*/
EnemyObjectStateAttack::EnemyObjectStateAttack()
{
}

/*
@fn �f�X�g���N�^
*/
EnemyObjectStateAttack::~EnemyObjectStateAttack()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
EnemyState EnemyObjectStateAttack::Update(EnemyObjectBase* _owner, float _deltaTime)
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
		velocity = trackingRotationVec * 100.0f;
		// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
		_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
	}

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void EnemyObjectStateAttack::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_ATTACK));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_ATTACK;

	_owner->SetState(State::Active);

	// �ǐՃ^�[�Q�b�g�̃|�C���^�𓾂�
	trackingObject = _owner->GetTrackingObject();
	// ���̃|�W�V��������ǐՃ^�[�Q�b�g�̃|�W�V�����ւ̕����x�N�g�����v�Z
	trackingRotationVec = trackingObject->GetPosition() - _owner->GetPosition();
	// �㉺�ړ������Ȃ��̂�0�ŌŒ�
	trackingRotationVec.z = 0.0f;
	// ���K��
	trackingRotationVec.Normalize();

	// ��]����
	RotationProcess(_owner, trackingRotationVec, _owner->GetCharaForwardVec());
}