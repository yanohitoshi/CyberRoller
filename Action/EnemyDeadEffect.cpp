#include "EnemyDeadEffect.h"

EnemyDeadEffect::EnemyDeadEffect(GameObject* _owner,const Vector3& _pos)
	: ParticleEffectBase(_pos, Vector3::Zero, 15, "Assets/Effect/Thunder_Thin.png", false)
	, AddScale(10.0f)
	, SubAlpha(0.05f)
	, RandValue(361)
	, EffectColor(Vector3(0.65f, 0.65f, 1.0f))
{
	// メンバー変数の初期化
	scale = 32;
	alpha = 1.0f;
	position = _pos;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(EffectColor);
	owner = _owner;

	RotateEffect();
}

EnemyDeadEffect::~EnemyDeadEffect()
{
}

void EnemyDeadEffect::UpdateGameObject(float _deltaTime)
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

void EnemyDeadEffect::RotateEffect()
{
	float radian;
	Quaternion rot;
	Quaternion target;

	//X軸をランダムな値回転させる
	radian = Math::ToRadians((float)(rand() % RandValue));
	rot = this->GetRotation();
	Quaternion incX(Vector3::UnitX, radian);
	target = Quaternion::Concatenate(rot, incX);
	SetRotation(target);

	//Y軸をランダムな値回転させる
	radian = Math::ToRadians((float)(rand() % RandValue));
	rot = this->GetRotation();
	Quaternion incY(Vector3::UnitY, radian);
	target = Quaternion::Concatenate(rot, incY);
	SetRotation(target);

	//Z軸をランダムな値回転させる
	radian = Math::ToRadians((float)(rand() % RandValue));
	rot = this->GetRotation();
	Quaternion incZ(Vector3::UnitZ, radian);
	target = Quaternion::Concatenate(rot, incZ);
	SetRotation(target);
}
