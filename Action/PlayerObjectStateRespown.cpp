//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateRespown.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateRespown::PlayerObjectStateRespown()
{
}

PlayerObjectStateRespown::~PlayerObjectStateRespown()
{
}

PlayerState PlayerObjectStateRespown::Update(PlayerObject* _owner, float _deltaTime)
{

	// owner�̃��X�|�[���t���O��false�ɃZ�b�g
	_owner->SetRespawnFlag(false);
	// owner����͉\��ԂɃZ�b�g
	_owner->SetIsAvailableInput(true);

	// �X�e�[�^�X���A�C�h�����O��ԂɕύX����
	state = PlayerState::PLAYER_STATE_IDLE;

	// �X�V���ꂽstate��Ԃ�
	return state;
}

void PlayerObjectStateRespown::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateRespown::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_IDLE));
	// state�����X�|�[����Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_RESPAWN;

}
