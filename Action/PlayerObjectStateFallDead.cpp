//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateFallDead.h"
#include "SkeletalMeshComponent.h"

/*
@fn �R���X�g���N�^
*/
PlayerObjectStateFallDead::PlayerObjectStateFallDead()
	: RespawnTime(120)
{
}

/*
@fn �f�X�g���N�^
*/
PlayerObjectStateFallDead::~PlayerObjectStateFallDead()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
*/
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

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void PlayerObjectStateFallDead::Enter(PlayerObject* _owner, float _deltaTime)
{

	// state��FALL_DEAD��Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_FALL_DEAD;

	// ���X�|�[���܂ł̃J�E���g��������
	respawnCount = 0;

	// ���͉\�t���O��false�ɃZ�b�g
	_owner->SetIsAvailableInput(false);
}

/*
@fn ���A�J�ڃJ�E���g�����֐�
@param	_owner �e�N���X�̃|�C���^
*/
void PlayerObjectStateFallDead::ToRespawnCountProcess(PlayerObject* _owner)
{
	// ���X�|�[������܂ł̎��Ԃ��J�E���g����
	++respawnCount;
	// �J�E���g���萔�l�ɓ��B������
	if (respawnCount >= RespawnTime)
	{
		// ���X�|�[���Ɉڍs����t���O��false�� 
		_owner->SetRespawnFlag(true);
		// owner�Ƀ��X�|�[������|�W�V������n��
		_owner->SetPosition(_owner->GetRespownPos());
		// ���S��ԃt���O��false��
		_owner->SetDeadFlag(false);
	}
}