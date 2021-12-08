//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CollectionLightEffect.h"
#include "CrystalEffectManager.h"

/*
@fn コンストラクタ
@param	親となるクラスのポインタ
@param	ポジション
@param	移動速度
*/
CollectionLightEffect::CollectionLightEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _direction, CrystalColor _crystalColor)
	: ParticleEffectBase(_pos, Vector3::Zero, 60, "Assets/Effect/Collection/Light.png", true)
	, AddScale(2.0f)
	, SubAlpha(0.01f)
	, InitAlpha(1.0f)
	, InitScale(32.0f)
	, AddValue(0.1f)
	, SpeedRandValue(400)
	, SpeedLowestValue(200)
	, SinRandValue(180)
{
	// メンバー変数の初期化
	owner = _owner;
	scale = InitScale;
	alpha = InitAlpha;
	position = _pos;
	direction = _direction;
	SetPosition(position);

	// ランダムな速度を得る
	speed = (float)(rand() % SpeedRandValue + SpeedLowestValue);
	// ランダムな初期の値を得る
	value = (float)(rand() % SinRandValue);
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

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
CollectionLightEffect::~CollectionLightEffect()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
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
		
		value += AddValue;
		sinV = Math::Sin(value);

		// sinの値を足すための変数
		Vector3 dir = Vector3::Zero;
		dir = direction;
		dir.x += sinV;
		dir.y += sinV;
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
