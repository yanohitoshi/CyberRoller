//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectStateDead.h"

/*
@fn �R���X�g���N�^
*/
EnemyObjectStateDead::EnemyObjectStateDead()
	: RespawnTime(200)
	, InvisibleTime(50)
	, FirstBlowAwayPower(100.0f)
	, BlowAwayPower(1.2f)
	, MaxSpeed(2000.0f)
{
}

/*
@fn �f�X�g���N�^
*/
EnemyObjectStateDead::~EnemyObjectStateDead()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
EnemyState EnemyObjectStateDead::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// �X�e�[�^�X�̃t���[�����Ԃ��v��
	++frameCount;

	// �ړ����x�ɐ�����ԗ͂𑫂�
	moveSpeed *= BlowAwayPower;

	// �ő呬�x�ɓ��B���Ă�����ő呬�x�ɌŒ肷��
	if (moveSpeed >= MaxSpeed)
	{
		moveSpeed = MaxSpeed;
	}

	// ��p���鑬�x�x�N�g���v�Z
	velocity = blowAwayDirection * moveSpeed;

	// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// ���Ԃ�������`���؂�
	if (frameCount >= InvisibleTime)
	{
		_owner->SetIsVisible(false);
		skeletalMeshComponent->SetVisible(false);
	}

	// ���Ԃ������烊�X�|�[��
	if (frameCount >= RespawnTime)
	{
		state = EnemyState::ENEMY_STATE_RESPAWN;
	}

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void EnemyObjectStateDead::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_DEAD));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_DEAD;
	// �X�e�[�^�X�𖳌���Ԃ�
	_owner->SetState(State::Disabling);
	// �t���[���J�E���g������
	frameCount = 0;
	// ������ԕ������v�Z
	blowAwayDirection = _owner->GetPosition() - _owner->GetDefeatedObjectPosition();

	// ������0�ɋ߂��Ȃ�������
	if (!Math::NearZero(blowAwayDirection.Length()))
	{
		// ���K��
		blowAwayDirection.Normalize();
	}

	// �㉺������0�ɌŒ�
	blowAwayDirection.z = 0.0f;
	// �ړ����x�������ɂ���
	moveSpeed = FirstBlowAwayPower;
}
