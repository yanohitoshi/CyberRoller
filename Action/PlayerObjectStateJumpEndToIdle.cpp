//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateJumpEndToIdle.h"
#include "SkeletalMeshComponent.h"
#include "SoundEffectComponent.h"

/*
@fn �R���X�g���N�^
@param _owner �e�N���X�̃|�C���^
*/
PlayerObjectStateJumpEndToIdle::PlayerObjectStateJumpEndToIdle(PlayerObject* _owner)
{
	soundEffect = new SoundEffectComponent(_owner, "Assets/Sound/SoundEffect/Player/Jump.wav");
}

/*
@fn �f�X�g���N�^
*/
PlayerObjectStateJumpEndToIdle::~PlayerObjectStateJumpEndToIdle()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
*/
PlayerState PlayerObjectStateJumpEndToIdle::Update(PlayerObject* _owner, float _deltaTime)
{

	// �ړ����x�Ƀf���^�^�C�����|���Ă�����|�W�V�����ɒǉ����čX�V
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// �A�j���[�V�����̍Đ����I����Ă�����
	if (!skeletalMeshComponent->IsPlaying())
	{
		// �X�e�[�^�X��ҋ@��Ԃɂ���
		state = PlayerState::PLAYER_STATE_IDLE;
	}

	// �W�����v�t���O�������̓X�C�b�`�W�����v�t���O��true��������
	if (_owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		// �X�e�[�^�X���W�����v�J�n��Ԃɂ���
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	// �ړ����͂������
	if (_owner->GetInputFlag())
	{
		// �X�e�[�^�X�𑖂�o����Ԃɂ���
		state = PlayerState::PLAYER_STATE_RUN_START;
	}

	// ���S��ԃ`�F�b�N
	CheckDeadFlag(_owner);
	// ���Ԑ؂�`�F�b�N
	CheckTimeOverFlag();

	// owner�ɑ��x���Z�b�g
	_owner->SetVelocity(velocity);

	// �X�V���ꂽstate��Ԃ�
	return state;
}

/*
@fn �C���v�b�g
@brief	state�ɉ����ē��͏������s��
@param	_owner �e�N���X�̃|�C���^
@param	_keyState ���͏��
*/
void PlayerObjectStateJumpEndToIdle::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// ���͉\��Ԃ�������
	if (_owner->GetIsAvailableInput())
	{
		// state�ύX�̉\���̂�����͂̃`�F�b�N
		CheckInput(_owner, _keyState);
	}
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void PlayerObjectStateJumpEndToIdle::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE;

	// �W�����v�͂��Z�b�g����
	_owner->SetJumpPower(_owner->GetFirstJumpPower());

	// ���n��ԂɂȂ����̂ŃW�����v���p�\�t���O��true�ɃZ�b�g
	_owner->SetIsAvailableJumpKey(true);

	// �W�����v�t���O��false�ɃZ�b�g
	_owner->SetJumpFlag(false);
	_owner->SetSwitchJumpFlag(false);

	// �W�����v�U���n�t���O������
	_owner->SetIsJumpAttck(false);
	_owner->SetIsAvailableJumpAttck(true);

	// ���͂�����Ȃ��l�����炤
	inputDeadSpace = _owner->GetDeadSpace();

	// �T�E���h�G�t�F�N�g��炷
	soundEffect->Play();
}