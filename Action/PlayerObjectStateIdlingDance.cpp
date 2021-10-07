//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateIdlingDance.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

// static�����o�[��������
bool PlayerObjectStateIdlingDance::isDancing = false;

/*
@fn �R���X�g���N�^
*/
PlayerObjectStateIdlingDance::PlayerObjectStateIdlingDance()
{
}

/*
@fn �f�X�g���N�^
*/
PlayerObjectStateIdlingDance::~PlayerObjectStateIdlingDance()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
PlayerState PlayerObjectStateIdlingDance::Update(PlayerObject* _owner, float _deltaTime)
{
	// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// �W�����v��ԂłȂ��ڒn��Ԃł��������
	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		// �X�e�[�^�X���W�����v���[�v��Ԃɂ���
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
		// �󒆂Ń_���X���Ȃ��悤�Ƀ_���X�t���O��false�ɕύX
		isDancing = false;
	}
	else if (_owner->GetInputFlag()) // �ړ����͂������
	{
		// �X�e�[�^�X�𑖂�o����Ԃɂ���
		state = PlayerState::PLAYER_STATE_RUN_START;
		// �󒆂Ń_���X���Ȃ��悤�Ƀ_���X�t���O��false�ɕύX
		isDancing = false;
	}
	else if (_owner->GetJumpFlag() || _owner->GetSwitchJumpFlag()) // �W�����v�t���O�������̓X�C�b�`�W�����v�t���O��true��������
	{
		// �X�e�[�^�X���W�����v�J�n��Ԃɂ���
		state = PlayerState::PLAYER_STATE_JUMPSTART;
		// �󒆂Ń_���X���Ȃ��悤�Ƀ_���X�t���O��false�ɕύX
		isDancing = false;
	}

	// ���S�t���O�������Ă�����
	if (_owner->GetDeadFlag())
	{
		// �X�e�[�^�X�����S��ԊJ�n�ɂ���
		state = PlayerState::PLAYER_STATE_DEAD;
		// �󒆂Ń_���X���Ȃ��悤�Ƀ_���X�t���O��false�ɕύX
		isDancing = false;
	}

	// �^�C���I�[�o�[�ɂȂ�����
	if (CountDownFont::GetTimeOverFlag() == true)
	{
		// �X�e�[�^�X���R���e�B�j���[�I���J�n��Ԃɂ���
		state = PlayerState::PLAYER_STATE_DOWNSTART;
		// �󒆂Ń_���X���Ȃ��悤�Ƀ_���X�t���O��false�ɕύX
		isDancing = false;
	}

	// �X�V���ꂽstate��Ԃ�
	return state;
}

/*
@fn �C���v�b�g
@brief	state�ɉ����ē��͏������s��
@param	_owner �e�N���X�̃|�C���^
@param	_keyState ���͏��
*/
void PlayerObjectStateIdlingDance::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// ���͉\��Ԃ�������
	if (_owner->GetIsAvailableInput())
	{
		// state�ύX�̉\���̂�����͂̃`�F�b�N
		ChackInput(_owner, _keyState);
	}
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void PlayerObjectStateIdlingDance::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_IDLE_DANCE));
	// state���_���X��Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_IDLE_DANCE;
	// �_���X�t���O��true�ɃZ�b�g
	isDancing = true;
}
