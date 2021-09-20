#include "PlayerTransformEffect.h"

PlayerTransformEffect::PlayerTransformEffect(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 10, "Assets/Effect/Particle7.png")
	, AddScale(1.0f)
	, SubAlpha(0.05f)
{
	// メンバー変数の初期化
	scale = 32.0f;
	alpha = 1.0f;
	speed = 50.0f;
	velocity = _velocity;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(Vector3(1.0f, 0.1f, 0.0f));
}

PlayerTransformEffect::~PlayerTransformEffect()
{
}

void PlayerTransformEffect::UpdateGameObject(float _deltaTime)
{
	// 生存時間のカウントダウン
	ParticleEffectBase::LifeCountDown();

	// ライフカウントが0以上
	if (lifeCount >= 0)
	{
		//// 定数を足して拡大
		//scale += AddScale;
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

	// ライフカウントが0以下
	if (lifeCount <= 0)
	{
		// ステータスをdeadに変更
		state = State::Dead;
	}
}