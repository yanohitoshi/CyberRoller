#include "PlayerObjectStateDead.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateDead::PlayerObjectStateDead()
	: respawnTime(120)
{
}

PlayerObjectStateDead::~PlayerObjectStateDead()
{
}

PlayerState PlayerObjectStateDead::Update(PlayerObject* _owner, float _deltaTime)
{
	// ���X�|�[���Ɉڍs����t���O��false��������
	if (_owner->GetRespawnFlag() == false)
	{
		// ���X�|�[������܂ł̎��Ԃ��J�E���g����
		++respawnCount;
		// �J�E���g���萔�l�ɓ��B������
		if (respawnCount >= respawnTime)
		{
			// ���X�|�[���Ɉڍs����t���O��false�� 
			_owner->SetRespawnFlag(true);
			// owner�Ƀ��X�|�[������|�W�V������n��
			_owner->SetPosition(_owner->GetRespownPos());
			// ���S��ԃt���O��false��
			_owner->SetDeadFlag(false);
		}
	}
	if (_owner->GetRespawnFlag()) 	// ���X�|�[���Ɉڍs����t���O��true��������
	{
		// �X�e�[�^�X�����X�|�[���ɕύX����
		state = PlayerState::PLAYER_STATE_RESPAWN;
	}

	// �X�V���ꂽstate��Ԃ�
	return state;
}

void PlayerObjectStateDead::Input(PlayerObject* _owner, const InputState& _keyState)
{

}

void PlayerObjectStateDead::Enter(PlayerObject* _owner, float _deltaTime)
{

	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();

	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DEAD));

	// state��DEAD��Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_DEAD;

	// ���X�|�[���܂ł̃J�E���g��������
	respawnCount = 0;

	// ���͉\�t���O��false�ɃZ�b�g
	_owner->SetIsAvailableInput(false);

}
