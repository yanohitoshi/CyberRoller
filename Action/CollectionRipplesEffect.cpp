//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CollectionRipplesEffect.h"

/*
@fn コンストラクタ
@param	親となるクラスのポインタ
@param	ポジション
@param	移動速度
*/
CollectionRipplesEffect::CollectionRipplesEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 20, "Assets/Effect/Collection/Ripple.png", true)
	, AddScale(32.0f)
	, SubAlpha(0.01f)
	, InitAlpha(1.0f)
	, InitScale(0.0f)
	, MoveSpeed(25.0f)
{
	// メンバー変数の初期化
	owner = _owner;
	scale = InitScale;
	alpha = InitAlpha;
	speed = MoveSpeed;
	position = _pos;
	velocity = _velocity;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(Vector3(0.9f, 0.9f, 0.5f));
	SetPosition(position);

}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
CollectionRipplesEffect::~CollectionRipplesEffect()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void CollectionRipplesEffect::UpdateGameObject(float _deltaTime)
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

		SetRotation(owner->GetRotation());
	}

	// ライフカウントが0以下
	if (lifeCount <= 0)
	{
		// ステータスをdeadに変更
		state = State::Dead;
	}
}