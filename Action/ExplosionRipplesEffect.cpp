//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ExplosionRipplesEffect.h"

/*
@fn コンストラクタ
@param	親となるクラスのポインタ
@param	ポジション
*/
ExplosionRipplesEffect::ExplosionRipplesEffect(GameObject* _owner, const Vector3& _pos)
	: ParticleEffectBase(_pos, Vector3::Zero, 20, "Assets/Effect/Bomb/Ripple.png", false)
	, AddScale(96.0f)
	, SubAlpha(0.03f)
	, EffectColor(Vector3(1.0f, 1.0f, 1.0f))
	, RandValue(271)
	, InitAlpha(1.0f)
	, InitScale(24.0f)
	, RotateLowestValue(90)
	, AxisYAngle(45.0f)
{
	// メンバー変数の初期化
	scale = InitScale;
	alpha = InitAlpha;
	position = _pos;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(EffectColor);
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);

	RotateEffect();
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
ExplosionRipplesEffect::~ExplosionRipplesEffect()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
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
	angle = (float)(rand() % RandValue + RotateLowestValue);
	Rotation(this, angle, Vector3::UnitX);
	angle = AxisYAngle;
	Rotation(this, angle, Vector3::UnitY);
	angle = (float)(rand() % RandValue + RotateLowestValue);
	Rotation(this, angle, Vector3::UnitZ);
}