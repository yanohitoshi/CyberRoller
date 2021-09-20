#include "JumpAttackEffect.h"

JumpAttackEffect::JumpAttackEffect(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 30, "Assets/Effect/Particle7.png")
	, AddScale(0.8f)
	, SubAlpha(0.05f)
{
	// メンバー変数の初期化
	scale = 128.0f;
	alpha = 0.6f;
	speed = 2.0f;
	velocity = _velocity;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	//particleComponent->SetColor(Vector3(0.93f, 0.93f, 0.93f));
	particleComponent->SetColor(Vector3(1.0f, 1.0f, 0.65f));
}

JumpAttackEffect::~JumpAttackEffect()
{
}

void JumpAttackEffect::UpdateGameObject(float _deltaTime)
{
	// 生存時間のカウントダウン
	ParticleEffectBase::LifeCountDown();

	// ライフカウントが0以上
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

	// ライフカウントが0以下
	if (lifeCount <= 0)
	{
		// ステータスをdeadに変更
		state = State::Dead;
	}
}
