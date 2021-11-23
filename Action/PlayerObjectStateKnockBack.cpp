//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateKnockBack.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

/*
@fn �R���X�g���N�^
*/
PlayerObjectStateKnockBack::PlayerObjectStateKnockBack()
	: knockBackFrameCount(0)
	, KnockBackSpeed(70.0f)
	, KnockBackTime(22)
{
}

/*
@fn �f�X�g���N�^
*/
PlayerObjectStateKnockBack::~PlayerObjectStateKnockBack()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
PlayerState PlayerObjectStateKnockBack::Update(PlayerObject* _owner, float _deltaTime)
{
	// �m�b�N�o�b�N�̎��Ԃ𐔂���
	++knockBackFrameCount;

	// ���x��ǉ�
	velocity += knockBackDirection * KnockBackSpeed;

	// �ڒn��������
	if (!_owner->GetOnGround())
	{
		// �d�͂�������
		velocity.z -= PlayerObject::GetGravity() * _deltaTime;
	}
	else
	{
		velocity.z = 0.0f;
	}

	// �m�b�N�o�b�N���Ԃ��߂�����
	if (knockBackFrameCount >= KnockBackTime)
	{
		velocity.Zero;
		_owner->SetVelocity(velocity);
		// �ǂɓ��������t���O��false��
		_owner->SetIsHitEnemy(false);
		// state���A�C�h�����O�ɕύX
		state = PlayerState::PLAYER_STATE_IDLE;
	}

	// �ړ����x�Ƀf���^�^�C�����|���Ă�����|�W�V�����ɒǉ����čX�V
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
	_owner->SetVelocity(velocity);
	
	// �����ɓ���������
	if (_owner->GetIsHitExplosion())
	{
		// ������я�ԂɑJ��
		state = PlayerState::PLAYER_STATE_BLOWAWAY;
	}

	// ���S��ԃ`�F�b�N
	CheckDeadFlag(_owner);

	// ���Ԑ؂�`�F�b�N
	CheckTimeOverFlag();

	// �X�V���ꂽstate��Ԃ�
	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void PlayerObjectStateKnockBack::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_KNOCKBACK));
	// state�����ݏ�Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_KNOCKBACK;

	// ���x������
	velocity = Vector3::Zero;
	// �J�E���g��������
	knockBackFrameCount = 0;

	// ���������G�l�~�[�̃|�W�V�������擾
	hitEnemyPosition = _owner->GetHitKnockBackObjectPosition();
	// �m�b�N�o�b�N��������x�N�g�����v�Z
	knockBackDirection = _owner->GetPosition() - hitEnemyPosition;

	// ������0�ɋ߂��Ȃ�������
	if (!Math::NearZero(knockBackDirection.Length()))
	{
		// ���K��
		knockBackDirection.Normalize();
	}

	// ��]����
	// �m�b�N�o�b�N�����������Ƌt�̕�������������̂�x,y����-1.0��������
	RotationProcess(_owner,Vector3(knockBackDirection.x * -1.0f, knockBackDirection.y * -1.0f,0.0f) ,_owner->GetCharaForwardVec());
}