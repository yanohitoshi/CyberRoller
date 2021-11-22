//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerTransformEffect.h"

/*
@fn コンストラクタ
@param	親となるクラスのポインタ
@param	ポジション
@param	移動速度
*/
PlayerTransformEffect::PlayerTransformEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 20, "Assets/Effect/Player/JumpAttack/Transform.png", false)
	, AddScale(16.0f)
	, SubAlpha(0.05f)
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
	particleComponent->SetColor(Vector3(1.0f, 1.0f, 1.0f));
	SetPosition(position);
	SetRotation(owner->GetRotation());
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
PlayerTransformEffect::~PlayerTransformEffect()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void PlayerTransformEffect::UpdateGameObject(float _deltaTime)
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
		// ポジションをセット
		SetRotation(owner->GetRotation());
	}

	// ライフカウントが0以下
	if (lifeCount <= 0)
	{
		// ステータスをdeadに変更
		state = State::Dead;
	}
}