//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "SandSmokeParticle.h"

SandSmokeParticle::SandSmokeParticle(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 25, "Assets/Effect/Particle_Soft.png")
	, AddScale(5.0f)
	, SubAlpha(0.05f)
{
	// メンバー変数の初期化
	scale = 16.0f;
	alpha = 1.0f;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	// 画像に付与する色を指定
	particleComponent->SetColor(Vector3(0.93f, 0.93f, 0.93f));
}

SandSmokeParticle::~SandSmokeParticle()
{
}

void SandSmokeParticle::UpdateGameObject(float _deltaTime)
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
		position += velocity * _deltaTime;
		// ポジションを更新
		SetPosition(position);
	}

	// ライフカウントが0以下になったら
	if (lifeCount < 0)
	{
		// ステータスをdeadに変更
		state = State::Dead;
	}
}
