//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameClearEffect.h"
#include "FireWorksEffectManager.h"

/*
@fn コンストラクタ
@param	ポジション
@param	移動速度
*/
GameClearEffect::GameClearEffect(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 10, "Assets/Effect/Clear/GameClear.png",true)
	, AddScale(10.0f)
	, SubAlpha(0.05f)
	, InitAlpha(1.0f)
	, InitScale(64.0f)
	, MoveSpeed(400.0f)
{
	// メンバー変数の初期化
	scale = InitScale;
	alpha = InitAlpha;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(Vector3(1.0f, 1.0f, 0.0f));
	speed = MoveSpeed;

	// 分岐させるエフェクトのマネージャークラスを追加
	new FireWorksEffectManager(this);

}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
GameClearEffect::~GameClearEffect()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void GameClearEffect::UpdateGameObject(float _deltaTime)
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
		position += velocity * speed * _deltaTime;
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