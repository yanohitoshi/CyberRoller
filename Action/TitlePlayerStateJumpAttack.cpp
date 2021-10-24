#include "TitlePlayerStateJumpAttack.h"
#include "TitlePlayerObject.h"
#include "TitleJumpAttackPlayerObject.h"
#include "SkeletalMeshComponent.h"

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return TitlePlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
*/
TitlePlayerState TitlePlayerStateJumpAttack::Update(TitlePlayerObject* _owner, float _deltaTime)
{
	// ���|�W�V�����ϐ�
	Vector3 tmpPosition;
	// ���`�⊮���Ƃ�ϐ��ɕۑ�
	tmpPosition = Vector3::Lerp(titleJumpAttackPlayerObject->GetPosition(), enterPosition, _deltaTime * 2.0f);
	// �|�W�V�������Z�b�g
	titleJumpAttackPlayerObject->SetPosition(tmpPosition);

	// ��]�p����萔�����Z
	rotationAngle -= JumpAttackRotationAngle;
	// ��]����
	titleJumpAttackPlayerObject->RotationProcess(rotationAngle,Vector3::UnitX);
	// �t���[���J�E���g�𐔂���
	++frameCount;

	// �W�����v�A�^�b�N�̎��Ԃ��߂��Ă�����
	if (JumpAttackTime <= frameCount)
	{
		// �I�[�i�[�ɑ���|�W�V���������
		Vector3 sendPosition = titleJumpAttackPlayerObject->GetPosition();
		// �ŏ��ɂ��炵�������炷
		sendPosition.z -= ShiftPositionZ;
		// �I�[�i�[�ɃW�����v�A�^�b�N�v���C���[�̃|�W�V������n��
		_owner->SetPosition(sendPosition);
		// �X�e�[�^�X���W�����v���[�v�ɕύX
		state = TitlePlayerState::JUMP_LOOP;
	}

    return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void TitlePlayerStateJumpAttack::Enter(TitlePlayerObject* _owner, float _deltaTime)
{
	// state��DEAD��Ԃɂ��ĕۑ�
	state = TitlePlayerState::JUMP_ATTACK;
	frameCount = 0;

	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �`�悳��Ă�����
	if (skeletalMeshComponent->GetVisible())
	{
		// �`���؂�
		skeletalMeshComponent->SetVisible(false);
	}

	// �I�[�i�[����^�C�g���p�W�����v�A�^�b�N�v���C���[�̃|�C���^�����炤
	titleJumpAttackPlayerObject = _owner->GetTitleJumpAttackPlayerObject();
	// �^�C�g���p�W�����v�A�^�b�N�v���C���[����meshComponent�̃|�C���^�����炤
	meshComponent = titleJumpAttackPlayerObject->GetMeshComponent();
	// �`�悳��Ă��Ȃ�������
	if (!meshComponent->GetVisible())
	{
		// �`�悷��
		meshComponent->SetVisible(true);
	}

	// �I�[�i�[�̃|�W�V���������炤
	enterPosition = _owner->GetPosition();
	// �������������炷
	enterPosition.z += ShiftPositionZ;
	// �W�����v�A�^�b�N�I�u�W�F�N�g�Ƀ|�W�V�������Z�b�g
	titleJumpAttackPlayerObject->SetPosition(enterPosition);

	// �I�t�Z�b�g�𑫂��ĖڕW�n�_�ɂ���
	enterPosition.y += Offset;
}