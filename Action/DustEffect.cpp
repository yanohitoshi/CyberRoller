#include "DustEffect.h"

/*
@fn コンストラクタ
@param	親となるクラスのポインタ
@param	ポジション
@param	移動速度
*/
DustEffect::DustEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, Vector3::Zero, 45, "Assets/Effect/BreakBlock/Dust.png", true)
	, AddScale(12.0f)
	, SubAlpha(0.02f)
	, EffectColor(Vector3(0.93f, 0.93f, 0.93f))
	, SpeedRandValue(50)
	, SpeedLowestValue(10)
{
	// メンバー変数の初期化
	scale = 0.0f;
	alpha = 1.0f;
	position = _pos;
	velocity = _velocity;
	speed = (float)(rand() % SpeedRandValue / SpeedLowestValue);
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(EffectColor);
	owner = _owner;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
DustEffect::~DustEffect()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void DustEffect::UpdateGameObject(float _deltaTime)
{
	// 生存時間のカウントダウン
	ParticleEffectBase::LifeCountDown();

	// ライフカウントが0以上にだったら
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
