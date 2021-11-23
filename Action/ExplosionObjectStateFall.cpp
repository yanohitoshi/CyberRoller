//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateFall.h"
#include "MeshComponent.h"

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return ExplosionObjectState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
*/
ExplosionObjectState ExplosionObjectStateFall::Update(ExplosionObjectBase* _owner, float _deltaTime)
{
	// �����鎞�Ԃ��J�E���g
	++fallCount;

	// �����鑬�x����
	velocity.z = -fallSpeed;

	// �|�W�V�����X�V
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// �_�ŏ���
	Flashing();

	// ��������I�u�W�F�N�g�ɓ����邩Z����0.0f�ȉ��ɂȂ�����
	if (_owner->GetIsHitExplosionObject() || _owner->GetPosition().z < 0.0f)
	{
		// �X�e�[�^�X�𔚔���ԂɑJ��
		state = ExplosionObjectState::EXPLOSION;
		return state;
	}

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void ExplosionObjectStateFall::Enter(ExplosionObjectBase* _owner, float _deltaTime)
{
	// �X�e�[�^�X�𗎉���ԂɕύX
	state = ExplosionObjectState::FALL;
	meshComponent = _owner->GetMeshComponent();
	// ���x��������
	velocity = Vector3::Zero;
	isRed = false;
	colorChangeTime = FirstColorChangeTime;
	fallCount = 0;
	angle = 0;
	_owner->SetState(State::Active);
	fallSpeed = _owner->GetFallSpeed();
}

/*
@fn �_�ŏ���
*/
void ExplosionObjectStateFall::Flashing()
{
	// �^�C�~���O��ς��鎞�Ԃ�������
	if (fallCount > FirstChangeRateTime)
	{
		// ��Ԗڂ̐F��ς��鎞�Ԃ���
		colorChangeTime = SecondColorChangeTime;
	}

	if (fallCount > SecondChangeRateTime)
	{
		// �O�Ԗڂ̐F��ς��鎞�Ԃ���
		colorChangeTime = ThirdColorChangeTime;
	}

	// �F��ύX����^�C�~���O��������
	if (fallCount % colorChangeTime == 0)
	{
		// �F�t���O��ύX
		if (isRed)
		{
			isRed = false;
		}
		else
		{
			isRed = true;
		}
	}

	// �F�����X�V
	if (isRed)
	{
		meshComponent->SetEmissiveColor(EmissiveColorRed);
	}
	else
	{
		meshComponent->SetEmissiveColor(EmissiveColorBlue);
	}
}
