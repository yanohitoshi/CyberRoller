#include "ExplosionRipplesEffect.h"

ExplosionRipplesEffect::ExplosionRipplesEffect(GameObject* _owner, const Vector3& _pos)
	: ParticleEffectBase(_pos, Vector3::Zero, 30, "Assets/Effect/Shockwave.png", false)
	, AddScale(12.0f)
	, SubAlpha(0.03f)
	, EffectColor(Vector3(1.0f, 1.0f, 1.0f))
	, RandValue(271)
{
	// メンバー変数の初期化
	scale = 0.0f;
	alpha = 0.0f;
	alpha = 1.0f;
	position = _pos;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(EffectColor);
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);

	RotateEffect();
}

ExplosionRipplesEffect::~ExplosionRipplesEffect()
{
}

void ExplosionRipplesEffect::UpdateGameObject(float _deltaTime)
{
	// 生存時間のカウントダウン
	ParticleEffectBase::LifeCountDown();

	// ライフカウントが0以上になったら
	if (lifeCount >= 0)
	{
		// 定数を足して拡大
		scale += AddScale;
		// 定数を引いて透過
		alpha -= SubAlpha;

		// scale値をセット
		particleComponent->SetScale(scale);
		// alpha値をセット
		particleComponent->SetAlpha(alpha);
	}

	// ライフカウントが0以下になったら
	if (lifeCount <= 0)
	{
		// ステータスをdeadに変更
		state = State::Dead;
	}
}


/*
@fn 回転処理関数
@brief	エフェクトの回転を行う
*/
void ExplosionRipplesEffect::RotateEffect()
{
	angle = (float)(rand() % RandValue + 90);
	Rotation(this, angle, Vector3::UnitX);
	angle = 45.0f;
	Rotation(this, angle, Vector3::UnitY);
	angle = (float)(rand() % RandValue + 90);
	Rotation(this, angle, Vector3::UnitZ);
}