#include "PlayerObjectStateDownStart.h"
#include "SkeletalMeshComponent.h"
PlayerObjectStateDownStart::PlayerObjectStateDownStart()
{
}

PlayerObjectStateDownStart::~PlayerObjectStateDownStart()
{
}

PlayerState PlayerObjectStateDownStart::Update(PlayerObject* _owner, float _deltaTime)
{
	// �d�͂Ƀf���^�^�C�����������l����
	velocity.z -= PlayerObject::GetGravity() * _deltaTime;

	// �������x���K��l�𒴂��Ă�����
	if (velocity.z <= MaxFallSpeed)
	{
		// �K��l�ɌŒ�
		velocity.z = MaxFallSpeed;
	}

	// �ړ����x�Ƀf���^�^�C�����|���Ă�����|�W�V�����ɒǉ����čX�V
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// �^�C���I�[�o�[���[�v�X�^�[�g��Ԃ̃A�j���[�V�������Đ�����Ă��Ȃ�������
	if (!skeletalMeshComponent->IsPlaying())
	{
		// �R���e�B�j���[�I����ԂɕύX
		state = PlayerState::PLAYER_STATE_DOWN_LOOP;
	}

	// owner�̕ϐ����X�V
	_owner->SetVelocity(velocity);

	// �X�V���ꂽstate��Ԃ�
	return state;
}

void PlayerObjectStateDownStart::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateDownStart::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DOWNSTART));
	// state���R���e�B�j���[���邩�I�������Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_DOWNSTART;

	// �I�[�i�[�̎����x���擾
	velocity = _owner->GetVelocity();
	// x����y���̑��x��0.0f�ɏ�����
	velocity.x = 0.0f;
	velocity.y = 0.0f;
}
