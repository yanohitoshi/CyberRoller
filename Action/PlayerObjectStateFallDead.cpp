#include "PlayerObjectStateFallDead.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateFallDead::PlayerObjectStateFallDead()
	: respawnTime(120)
{
}

PlayerObjectStateFallDead::~PlayerObjectStateFallDead()
{
}

PlayerState PlayerObjectStateFallDead::Update(PlayerObject* _owner, float _deltaTime)
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

	// ���X�|�[���Ɉڍs����t���O��false��������
	if (_owner->GetRespawnFlag() == false)
	{
		// ���A�܂ł̃J�E���g����
		ToRespawnCountProcess(_owner);
	}

	if (_owner->GetRespawnFlag()) 	// ���X�|�[���Ɉڍs����t���O��true��������
	{
		// �X�e�[�^�X�����X�|�[���ɕύX����
		state = PlayerState::PLAYER_STATE_RESPAWN;
	}

	// �X�V���ꂽstate��Ԃ�
	return state;
}

void PlayerObjectStateFallDead::Input(PlayerObject* _owner, const InputState& _keyState)
{

}

void PlayerObjectStateFallDead::Enter(PlayerObject* _owner, float _deltaTime)
{

	// state��FALL_DEAD��Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_FALL_DEAD;

	// ���X�|�[���܂ł̃J�E���g��������
	respawnCount = 0;

	// ���͉\�t���O��false�ɃZ�b�g
	_owner->SetIsAvailableInput(false);
}

void PlayerObjectStateFallDead::ToRespawnCountProcess(PlayerObject* _owner)
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
