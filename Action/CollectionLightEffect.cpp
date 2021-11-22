#include "CollectionLightEffect.h"
#include "CrystalEffectManager.h"

CollectionLightEffect::CollectionLightEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _direction, CrystalColor _crystalColor)
	: ParticleEffectBase(_pos, Vector3::Zero, 60, "Assets/Effect/Collection/Light.png", true)
	, AddScale(2.0f)
	, SubAlpha(0.01f)
{
	// メンバー変数の初期化
	owner = _owner;
	scale = 32.0f;
	alpha = 1.0f;
	position = _pos;
	direction = _direction;
	SetPosition(position);

	// ランダムな速度を得る
	speed = (float)(rand() % 400 + 200);
	// ランダムな初期の値を得る
	value = (float)(rand() % 180);
	sinV = Math::Sin(value);

	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);

	// マネージャークラスから受け取った色情報を参照して色の設定
	if (_crystalColor == CrystalColor::WHITE)
	{
		particleComponent->SetColor(Vector3(0.9f, 0.9f, 0.9f));
	}
	else if (_crystalColor == CrystalColor::RED)
	{
		particleComponent->SetColor(Vector3(1.0f, 0.5f, 0.5f));
	}
	else if (_crystalColor == CrystalColor::BLUE)
	{
		particleComponent->SetColor(Vector3(0.5f, 0.5f, 1.0f));
	}
	else if (_crystalColor == CrystalColor::GREEN)
	{
		particleComponent->SetColor(Vector3(0.5f, 1.0f, 0.5f));
	}

}

CollectionLightEffect::~CollectionLightEffect()
{
}

void CollectionLightEffect::UpdateGameObject(float _deltaTime)
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
		
		value += 0.1f;
		sinV = Math::Sin(value);

		// sinの値を足すための変数
		Vector3 dir = Vector3::Zero;
		dir = direction;
		dir.x += sinV;
		dir.y += sinV;
		//dir.Normalize();
		velocity = dir * speed;

		SetPosition(position + velocity * _deltaTime);
	}

	// ライフカウントが0以下
	if (lifeCount <= 0)
	{
		// ステータスをdeadに変更
		state = State::Dead;
	}
}
