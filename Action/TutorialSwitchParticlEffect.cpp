//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TutorialSwitchParticlEffect.h"

/*
@brief	コンストラクタ
@param	ポジション
@param	オーナーとなるGameObject型ポインタ
*/
TutorialSwitchParticlEffect::TutorialSwitchParticlEffect(const Vector3& _pos, GameObject* _owner)
	: ParticleEffectBase(_pos, Vector3::Zero,100, "Assets/Particle/Tutorial/Switch/switch_tutorial_touch.png", 1.0f)
	, InitScale(128.0f)
{
	// ParticleComponent初期化
	particleComponent->SetOffSet(Vector3(0.0f, 0.0f, 0.0f));
	particleComponent->SetVisible(false);
	particleComponent->SetScale(InitScale);
	// 変数初期化
	owner = _owner;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
TutorialSwitchParticlEffect::~TutorialSwitchParticlEffect()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void TutorialSwitchParticlEffect::UpdateGameObject(float _deltaTime)
{
	// 親ののフラグを見て描画を切り替える
	if (owner->GetSwitchFlag() == false)
	{
		particleComponent->SetVisible(true);
	}
	else if (owner->GetSwitchFlag() == true)
	{
		particleComponent->SetVisible(false);
	}
}