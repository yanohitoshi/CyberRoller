#include "TitlePlayerStateJumpLoop.h"
#include "TitlePlayerObject.h"
#include "SkeletalMeshComponent.h"
#include "TitleJumpAttackPlayerObject.h"

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return TitlePlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
*/
TitlePlayerState TitlePlayerStateJumpLoop::Update(TitlePlayerObject* _owner, float _deltaTime)
{
	// �W�����v���̃J�E���g�𐔂���
	++jumpFrameCount;

	// �W�����v���̃J�E���g���K��l�ȉ���������
	if (jumpFrameCount < JumpLimitTime)
	{
		// ����ɃW�����v�͂�ǉ�
		jumpPower += JumpSpeed;
	}

	// �d�͂�������
	jumpPower -= Gravity * _deltaTime;

	// �W�����v�͂�ǉ�
	velocity.z = jumpPower;

	// �������x���K��l�𒴂��Ă�����
	if (velocity.z <= MaxFallSpeed)
	{
		// �������x���K��l�ɌŒ肷��
		velocity.z = MaxFallSpeed;
	}

	// �|�W�V�������X�V
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// �㉺�����̑��x��0�ȉ��ŃW�����v�����񐔂�3�ȏ�Ȃ�
	if (velocity.z <= 0.0f && _owner->GetJumpCount() >= 3)
	{
		// �W�����v�����񐔂�������
		_owner->SetJumpCount(0);
		// �X�e�[�^�X���W�����v�A�^�b�N�ɕύX
		state = TitlePlayerState::JUMP_ATTACK;
	}

	// �|�W�V�������ڒn�ʒu��菬�����Ȃ��Ă�����
	if (_owner->GetPosition().z <= OnGroundCoordinate)
	{
		// �W�����v�t���O��false��
		_owner->SetJumpFlag(false);
		// �X�e�[�^�X�𑖂��Ԃ�
		state = TitlePlayerState::RUN;
	}

    return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void TitlePlayerStateJumpLoop::Enter(TitlePlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(TitlePlayerState::JUMP_LOOP));

	if (!skeletalMeshComponent->GetVisible())
	{
		skeletalMeshComponent->SetVisible(true);
	}

	// �I�[�i�[����^�C�g���p�W�����v�A�^�b�N�v���C���[�̃|�C���^�����炤
	titleJumpAttackPlayerObject = _owner->GetTitleJumpAttackPlayerObject();
	// �^�C�g���p�W�����v�A�^�b�N�v���C���[����meshComponent�̃|�C���^�����炤
	meshComponent = titleJumpAttackPlayerObject->GetMeshComponent();
	if (meshComponent->GetVisible())
	{
		meshComponent->SetVisible(false);
	}
	// state��DEAD��Ԃɂ��ĕۑ�
	state = TitlePlayerState::JUMP_LOOP;

	// ������
	jumpFrameCount = _owner->GetJumpFrameCount();
	jumpPower = _owner->GetJumpPower();
}