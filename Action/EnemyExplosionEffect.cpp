#include "EnemyExplosionEffect.h"

EnemyExplosionEffect::EnemyExplosionEffect(GameObject* _owner, const Vector3& _pos,const Vector3& _velocity)
	: ParticleEffectBase(_pos, Vector3::Zero, 30, "Assets/Effect/glow.png", true)
	, AddScale(12.0f)
	, SubAlpha(0.02f)
	, EffectColor(Vector3(0.65f, 0.65f, 1.0f))
	, EnableTime(60)
{
	// メンバー変数の初期化
	scale = 16.0f;
	alpha = 0.0f;
	position = _pos;
	velocity = _velocity;
	speed = 3.0f;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(EffectColor);
	owner = _owner;
	enableCount = 0;
	isEnabled = false;
}

EnemyExplosionEffect::~EnemyExplosionEffect()
{
}

void EnemyExplosionEffect::UpdateGameObject(float _deltaTime)
{
	++enableCount;

	if (enableCount >= EnableTime)
	{
		if (!isEnabled)
		{
			isEnabled = true;
			alpha = 1.0f;
			particleComponent->SetAlpha(alpha);
		}

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
}

