//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TutorialSwitchParticlEffect.h"

TutorialSwitchParticlEffect::TutorialSwitchParticlEffect(const Vector3& _pos, GameObject* _owner)
	: ParticleEffectBase(_pos, Vector3::Zero,100, "Assets/Particle/switch_tutorial_touch.png", 1.0f)
	, InitScale(128.0f)
{
	// ParticleComponent������
	particleComponent->SetOffSet(Vector3(0.0f, 0.0f, 0.0f));
	particleComponent->SetVisible(false);
	particleComponent->SetScale(InitScale);
	// �ϐ�������
	owner = _owner;
}

TutorialSwitchParticlEffect::~TutorialSwitchParticlEffect()
{
}

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
