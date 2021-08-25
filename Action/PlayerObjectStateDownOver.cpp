//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateDownOver.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateDownOver::PlayerObjectStateDownOver()
{
}

PlayerObjectStateDownOver::~PlayerObjectStateDownOver()
{
}

PlayerState PlayerObjectStateDownOver::Update(PlayerObject* _owner, float _deltaTime)
{
	// �X�V���ꂽstate��Ԃ�
	return state;
}

void PlayerObjectStateDownOver::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateDownOver::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DOWN_OVER));
	// state���Q�[���I�[�o�[��Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_DOWN_OVER;
}
