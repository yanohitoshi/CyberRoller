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
	// �^�C���I�[�o�[���[�v�X�^�[�g��Ԃ̃A�j���[�V�������Đ�����Ă��Ȃ�������
	if (!skeletalMeshComponent->IsPlaying())
	{
		// �R���e�B�j���[�I����ԂɕύX
		state = PlayerState::PLAYER_STATE_DOWN_LOOP;
	}

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
}
