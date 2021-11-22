//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "JumpAttackEffect.h"

/*
@fn コンストラクタ
@param	ポジション
@param	移動速度
*/
JumpAttackEffect::JumpAttackEffect(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 45, "Assets/Effect/Player/JumpAttack/Attack.png", true)
	, AddScale(1.0f)
	, SubAlpha(0.05f)
	, InitAlpha(1.0f)
	, InitScale(128.0f)
{
	// メンバー変数の初期化
	scale = InitScale;
	alpha = InitAlpha;
	velocity = _velocity;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(Vector3(0.3f, 0.3f, 1.0f));
	// Particleのブレンドモードをセット
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
JumpAttackEffect::~JumpAttackEffect()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
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