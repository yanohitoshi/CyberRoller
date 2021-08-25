//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TutorialSwitchOkEffect.h"

TutorialSwitchOkEffect::TutorialSwitchOkEffect(const Vector3& _pos, GameObject* _owner)
	: ParticleEffectBase(_pos, Vector3::Zero, 100, "Assets/Particle/touch_OK.png", 1.0f)
	, InitScale(128.0f)
{
	// ParticleComponent初期化
	particleComponent->SetOffSet(Vector3(0.0f, 0.0f, 0.0f));
	particleComponent->SetVisible(false);
	particleComponent->SetScale(InitScale);
	// 変数初期化
	owner = _owner;
}

TutorialSwitchOkEffect::~TutorialSwitchOkEffect()
{
}

void TutorialSwitchOkEffect::UpdateGameObject(float _deltaTime)
{
	// 親ののフラグを見て描画を切り替える
	if (owner->GetSwitchFlag() == true)
	{
		particleComponent->SetVisible(true);
	}
	else if (owner->GetSwitchFlag() == false)
	{
		particleComponent->SetVisible(false);
	}

}
