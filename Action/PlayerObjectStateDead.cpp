//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateDead.h"
#include "SkeletalMeshComponent.h"
#include "SoundEffectComponent.h"
/*
@fn �R���X�g���N�^
*/
PlayerObjectStateDead::PlayerObjectStateDead(PlayerObject* _owner)
	: RespawnTime(120)
{
	soundEffect = new SoundEffectComponent(_owner, "Assets/Sound/SoundEffect/Player/Down.wav");
}

/*
@fn �f�X�g���N�^
*/
PlayerObjectStateDead::~PlayerObjectStateDead()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
PlayerState PlayerObjectStateDead::Update(PlayerObject* _owner, float _deltaTime)
{
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

	soundEffect->Play();
}

/*
@fn ���A�J�ڃJ�E���g�����֐�
@param	_owner �e�N���X�̃|�C���^
*/
void PlayerObjectStateDead::ToRespawnCountProcess(PlayerObject* _owner)
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
