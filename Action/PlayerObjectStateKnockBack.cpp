//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateKnockBack.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateKnockBack::PlayerObjectStateKnockBack()
{
}

PlayerObjectStateKnockBack::~PlayerObjectStateKnockBack()
{
}

PlayerState PlayerObjectStateKnockBack::Update(PlayerObject* _owner, float _deltaTime)
{
	if (!_owner->GetOnGround())
	{
		// �d�͂Ƀf���^�^�C�����������l����
		velocity.z -= PlayerObject::GetGravity() * _deltaTime;
		velocity += knockBackDirection * 10.0f;
		velocity.z += 50.0f;

		// �ڒn������
		if (_owner->GetOnGround())
		{
			velocity.x = 0.0f;
			velocity.y = 0.0f;
			_owner->SetVelocity(velocity);
			// �ǂɓ��������t���O��false��
			_owner->SetIsHitEnemy(false);
			// state���A�C�h�����O�ɕύX
			state = PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE;
		}
	}
	else
	{
		velocity += knockBackDirection * 25.0f;

		if (!skeletalMeshComponent->IsPlaying())
		{
			velocity.x = 0.0f;
			velocity.y = 0.0f;
			_owner->SetVelocity(velocity);
			// �ǂɓ��������t���O��false��
			_owner->SetIsHitEnemy(false);
			// state���A�C�h�����O�ɕύX
			state = PlayerState::PLAYER_STATE_IDLE;
		}

	}

	// �ړ����x�Ƀf���^�^�C�����|���Ă�����|�W�V�����ɒǉ����čX�V
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
	_owner->SetVelocity(velocity);
	

	//else if (!skeletalMeshComponent->IsPlaying() && !_owner->GetOnGround())
	//{
	//	_owner->SetVelocity(velocity);
	//	// �ǂɓ��������t���O��false��
	//	_owner->SetIsHitEnemy(false);
	//	// state���A�C�h�����O�ɕύX
	//	state = PlayerState::PLAYER_STATE_JUMPLOOP;
	//}

	// ���S�t���O�������Ă�����
	if (_owner->GetDeadFlag())
	{
		state = PlayerState::PLAYER_STATE_DEAD;
	}

	// �^�C���I�[�o�[�t���O��true��������
	if (CountDownFont::GetTimeOverFlag() == true)
	{
		// �X�e�[�^�X���R���e�B�j���[�I���J�n��Ԃɂ���
		state = PlayerState::PLAYER_STATE_DOWNSTART;
	}

	// �X�V���ꂽstate��Ԃ�
	return state;
}

void PlayerObjectStateKnockBack::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateKnockBack::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_KNOCKBACK));
	// state�����ݏ�Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_KNOCKBACK;
	//// �ړ��x�N�g����0.0f�ɐݒ�
	//_owner->SetVelocity(Vector3::Zero);

	hitEnemyPosition = _owner->GetHitEnemyPosition();
	knockBackDirection = _owner->GetPosition() - hitEnemyPosition;
	knockBackDirection.z = 0.0f;
	knockBackDirection.Normalize();

	RotationProcess(_owner, knockBackDirection * -1.0f,_owner->GetCharaForwardVec());

	if (!_owner->GetOnGround())
	{
    	velocity.z = 500.0f;
	}
}