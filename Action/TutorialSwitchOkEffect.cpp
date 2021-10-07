//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TutorialSwitchOkEffect.h"

/*
@brief	�R���X�g���N�^
@param	�|�W�V����
@param	�I�[�i�[�ƂȂ�GameObject�^�|�C���^
*/
TutorialSwitchOkEffect::TutorialSwitchOkEffect(const Vector3& _pos, GameObject* _owner)
	: ParticleEffectBase(_pos, Vector3::Zero, 100, "Assets/Particle/touch_OK.png", 1.0f)
	, InitScale(128.0f)
{
	// ParticleComponent������
	particleComponent->SetOffSet(Vector3(0.0f, 0.0f, 0.0f));
	particleComponent->SetVisible(false);
	particleComponent->SetScale(InitScale);
	// �ϐ�������
	owner = _owner;
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
TutorialSwitchOkEffect::~TutorialSwitchOkEffect()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void TutorialSwitchOkEffect::UpdateGameObject(float _deltaTime)
{
	// �e�̂̃t���O�����ĕ`���؂�ւ���
	if (owner->GetSwitchFlag() == true)
	{
		particleComponent->SetVisible(true);
	}
	else if (owner->GetSwitchFlag() == false)
	{
		particleComponent->SetVisible(false);
	}
}