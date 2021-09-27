#include "PlayerAttackHitEffectRipples.h"

PlayerAttackHitEffectRipples::PlayerAttackHitEffectRipples(GameObject* _owner, const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 5, "Assets/Effect/Shockwave.png", false)
	, AddScale(128.0f)
	, SubAlpha(0.01f)
{
	// メンバー変数の初期化
	owner = _owner;
	scale = 0.0f;
	alpha = 1.0f;
	speed = 25.0f;
	position = _pos;
	velocity = _velocity;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(Vector3(1.0f, 0.8f, 0.4f));
	SetPosition(position);
	SetRotation(owner->GetRotation());
}

PlayerAttackHitEffectRipples::~PlayerAttackHitEffectRipples()
{
}

void PlayerAttackHitEffectRipples::UpdateGameObject(float _deltaTime)
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

		SetRotation(owner->GetRotation());
	}

	// ライフカウントが0以下
	if (lifeCount <= 0)
	{
		// ステータスをdeadに変更
		state = State::Dead;
	}
}