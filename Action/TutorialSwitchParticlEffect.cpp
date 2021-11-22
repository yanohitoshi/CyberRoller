//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TutorialSwitchParticlEffect.h"

/*
@brief	�R���X�g���N�^
@param	�|�W�V����
@param	�I�[�i�[�ƂȂ�GameObject�^�|�C���^
*/
TutorialSwitchParticlEffect::TutorialSwitchParticlEffect(const Vector3& _pos, GameObject* _owner)
	: ParticleEffectBase(_pos, Vector3::Zero,100, "Assets/Particle/Tutorial/Switch/switch_tutorial_touch.png", 1.0f)
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
TutorialSwitchParticlEffect::~TutorialSwitchParticlEffect()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void TutorialSwitchParticlEffect::UpdateGameObject(float _deltaTime)
{
	// �e�̂̃t���O�����ĕ`���؂�ւ���
	if (owner->GetSwitchFlag() == false)
	{
		particleComponent->SetVisible(true);
	}
	else if (owner->GetSwitchFlag() == true)
	{
		particleComponent->SetVisible(false);
	}
}