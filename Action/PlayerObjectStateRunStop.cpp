//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateRunStop.h"
#include "SkeletalMeshComponent.h"

/*
@fn �R���X�g���N�^
*/
PlayerObjectStateRunStop::PlayerObjectStateRunStop()
	: TurnDelayValue(30)
	, TurnValue(10)
{
}

/*
@fn �f�X�g���N�^
*/
PlayerObjectStateRunStop::~PlayerObjectStateRunStop()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
PlayerState PlayerObjectStateRunStop::Update(PlayerObject* _owner, float _deltaTime)
{
	// �^�[���L���J�E���g�𐔂���
	++isTurnCount;

	// �ړ����x��0.0f�ȏゾ������
	if (moveSpeed >= 0.0f)
	{
		// ����������
		moveSpeed -= decelerationForce;
	}

	// owner�̕����x�N�g���Ɉړ����x���|���Ĉړ��x�N�g�����X�V
	velocity.x = _owner->GetCharaForwardVec().x * moveSpeed;
	velocity.y = _owner->GetCharaForwardVec().y * moveSpeed;

	// �ړ��x�N�g���Ƀf���^�^�C�����|���Ă�����|�W�V�����ɒǉ����čX�V
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// �A�j���[�V�����̍Đ����I����Ă���������͈ړ����x��0.0f�ȉ��ɂȂ��Ă�����
	if (!skeletalMeshComponent->IsPlaying() || moveSpeed <= 0.0f)
	{
		// �X�e�[�^�X��ҋ@��Ԃɂ���
		state = PlayerState::PLAYER_STATE_IDLE;
	}

	// �ړ����͂������ă^�[������Ԋu�̃J�E���g���K��l�ȏ�Ń^�[���ɓ����J�E���g���K��l�ȏゾ������
	if (_owner->GetInputFlag() && _owner->GetTurnDelayCount() >= TurnDelayValue && isTurnCount <= TurnValue)
	{
		// �X�e�[�^�X���^�[����Ԃɂ���
		state = PlayerState::PLAYER_STATE_RUN_TURN;
	}

	// �W�����v�t���O�������̓X�C�b�`�W�����v�t���O��true��������
	if (_owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		// �X�e�[�^�X���W�����v�J�n��Ԃɂ���
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	// �W�����v�t���O��false�Őڒn��Ԃł��������
	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		// �X�e�[�^�X���W�����v���[�v�ɂ���
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

	// ���S��ԃ`�F�b�N
	CheckDeadFlag(_owner);

	// ���Ԑ؂�`�F�b�N
	CheckTimeOverFlag();

	// owner�̕ϐ����X�V
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
void PlayerObjectStateRunStop::Input(PlayerObject* _owner, const InputState& _keyState)
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
void PlayerObjectStateRunStop::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_RUN_STOP));
	// state�𑖂�I����Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_RUN_STOP;
	// owner�̈ړ����x�����炤
	moveSpeed = _owner->GetMoveSpeed();
	// �^�[���ɉ\�J�E���g��������
	isTurnCount = 0;
	// �����͂����炤
	decelerationForce = _owner->GetDecelerationForce();
	// ���͂�����Ȃ��l�����炤
	inputDeadSpace = _owner->GetDeadSpace();
}
