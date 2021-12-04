//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateStartExplosion.h"
#include "MeshComponent.h"
#include "SoundEffectComponent.h"

ExplosionObjectStateStartExplosion::ExplosionObjectStateStartExplosion(ExplosionObjectBase* _owner)
	: BlowAwaySpeed(1600.0f)
	, FirstColorChangeTime(15)
	, ExplosionStartTime(180)
{
	soundEffectComponent = new SoundEffectComponent(_owner, "Assets/Sound/SoundEffect/Explosion/Explosion2.wav");
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return ExplosionObjectState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
*/
ExplosionObjectState ExplosionObjectStateStartExplosion::Update(ExplosionObjectBase* _owner, float _deltaTime)
{
	// ���Ԍv��
	++explosionStart;

	// �W�����v�A�^�b�N�v���C���[�ɍ~��Ă��Ȃ����
	if (!isHitJumpAttackPlayer)
	{
		// ���Ԃ�����܂ł��̏�Œ�~
		if (explosionStart > ExplosionStartTime)
		{
			// ���Ԃ������甚��
			state = ExplosionObjectState::EXPLOSION;
			return state;
		}

	}
	else
	{
		// ���Ԃ�����������͓��������瑦��������I�u�W�F�N�g�ɐG�ꂽ��
		if (explosionStart > ExplosionStartTime || _owner->GetIsHitExplosionObject())
		{
			// ����
			state = ExplosionObjectState::EXPLOSION;
			return state;
		}
		// ���ԓ��͉�]���Ȃ���ړ�
		velocity = blowAwayDirection * BlowAwaySpeed;
		_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
		angle += 0.1f;
		RotationProcess(_owner, angle, Vector3::UnitY);
	}

	// �_�ŏ���
	Flashing();

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void ExplosionObjectStateStartExplosion::Enter(ExplosionObjectBase* _owner, float _deltaTime)
{
	// �X�e�[�^�X�𔚔��J�n��ԂɃZ�b�g
	state = ExplosionObjectState::EXPLOSION_START;
	meshComponent = _owner->GetMeshComponent();
	// ���x��������
	velocity = Vector3::Zero;

	// ������ԕ������v�Z
	isHitJumpAttackPlayer = _owner->GetIsHitJumpAttackPlayer();
	blowAwayDirection = _owner->GetPosition() - _owner->GetHitPosition();
	if (!Math::NearZero(blowAwayDirection.Length()))
	{
		blowAwayDirection.Normalize();
	}
	blowAwayDirection.z = 0.0f;

	// �ϐ�������
	isRed = false;
	colorChangeTime = FirstColorChangeTime;
	explosionStart = 0;
	angle = 0;
	_owner->SetState(State::Disabling);

	//// ���ʉ���炷
	//soundEffectComponent->Play();

}

void ExplosionObjectStateStartExplosion::Flashing()
{
	// �^�C�~���O��ς��鎞�Ԃ�������
	if (explosionStart > FirstChangeRateTime)
	{
		// ��Ԗڂ̐F��ς��鎞�Ԃ���
		colorChangeTime = SecondColorChangeTime;
	}

	if (explosionStart > SecondChangeRateTime)
	{
		// �O�Ԗڂ̐F��ς��鎞�Ԃ���
		colorChangeTime = ThirdColorChangeTime;
	}

	// �F��ύX����^�C�~���O��������
	if (explosionStart % colorChangeTime == 0)
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
