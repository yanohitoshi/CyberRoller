#include "ExplosionEffect.h"

ExplosionEffect::ExplosionEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, Vector3::Zero, 30, "Assets/Effect/Particle04_bokashistrong_soft.png", true)
	, AddScale(8.0f)
	, SubAlpha(0.02f)
	, EffectColor(Vector3(0.68f, 0.85f, 0.9f))
{
	// メンバー変数の初期化
	scale = 0.0f;
	alpha = 0.0f;
	alpha = 1.0f;
	position = _pos;
	velocity = _velocity;
	speed = rand() % 50 / 10.0f;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(EffectColor);
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);
}

ExplosionEffect::~ExplosionEffect()
{
}

void ExplosionEffect::UpdateGameObject(float _deltaTime)
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

		// ポジションに速度を追加
		position += velocity * speed;
		// ポジションを更新
		SetPosition(position);
	}

	// ライフカウントが0以下になったら
	if (lifeCount <= 0)
	{
		// ステータスをdeadに変更
		state = State::Dead;
	}
}
