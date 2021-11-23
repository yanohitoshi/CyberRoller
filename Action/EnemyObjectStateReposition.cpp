//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectStateReposition.h"

/*
@fn �R���X�g���N�^
*/
EnemyObjectStateReposition::EnemyObjectStateReposition()
	: IdlingLength(2.0f)
{
}

/*
@fn �f�X�g���N�^
*/
EnemyObjectStateReposition::~EnemyObjectStateReposition()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
EnemyState EnemyObjectStateReposition::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// �ǐՃ^�[�Q�b�g�����Ȃ��ꍇ
	if (!_owner->GetIsTracking())
	{
		// ���|�W�V�����ϐ�
		Vector3 tmpPosition;
		// ���̃|�W�V�����Ə����|�W�V�����Ő��`��Ԃ����
		tmpPosition = Vector3::Lerp(_owner->GetPosition(), firstPosition, _deltaTime * 1.0f);
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
	Vector3 checkReposition = repositionRotationVec;
	// ���K��
	repositionRotationVec.Normalize();
	// ��]����
	RotationProcess(_owner, repositionRotationVec, _owner->GetCharaForwardVec());

	// �������擾
	float Length = checkReposition.Length();

	// �������K��l�ȉ��̏ꍇ�A�C�h�����O��Ԃֈڍs
	if (Length <= IdlingLength)
	{
		state = EnemyState::ENEMY_STATE_IDLE;
	}

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void EnemyObjectStateReposition::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_REPOSITION;
	// �X�e�[�^�X��Active�ɂ���
	_owner->SetState(State::Active);

	// �I�[�i�[�̈ړ����x�𓾂�
	moveSpeed = _owner->GetMoveSpeed();
	// �I�[�i�[�̏����|�W�V�����𓾂�
	firstPosition = _owner->GetFirstPosition();
	// ���̃|�W�V�������珉���|�W�V�����ւ̕����x�N�g�����v�Z
	repositionRotationVec = firstPosition - _owner->GetPosition();

	// ������0�ɋ߂��Ȃ�������
	if (!Math::NearZero(repositionRotationVec.Length()))
	{
		// ���K��
		repositionRotationVec.Normalize();
	}

	// ��]����
	RotationProcess(_owner, repositionRotationVec, _owner->GetCharaForwardVec());
}
