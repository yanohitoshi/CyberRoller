//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateKnockBack.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateKnockBack::PlayerObjectStateKnockBack()
	: knockBackFrameCount(0)
{
}

PlayerObjectStateKnockBack::~PlayerObjectStateKnockBack()
{
}

PlayerState PlayerObjectStateKnockBack::Update(PlayerObject* _owner, float _deltaTime)
{

	++knockBackFrameCount;

	if (!_owner->GetOnGround())
	{
		// �d�͂Ƀf���^�^�C�����������l����
		velocity.z -= PlayerObject::GetGravity() * _deltaTime;
	}

	velocity += knockBackDirection * 50.0f;

	velocity.z = 0.0f;
	if (knockBackFrameCount >= 22 )
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

	velocity = Vector3::Zero;

	knockBackFrameCount = 0;

	hitEnemyPosition = _owner->GetHitEnemyPosition();
	knockBackDirection = _owner->GetPosition() - hitEnemyPosition;

	knockBackDirection.Normalize();

	RotationProcess(_owner,Vector3(knockBackDirection.x * -1.0f, knockBackDirection.y * -1.0f,0.0f) ,_owner->GetCharaForwardVec());


}