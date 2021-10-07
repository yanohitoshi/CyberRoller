//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CrystalDefaultEffect.h"
#include "CrystalEffectManager.h"

/*
@fn コンストラクタ
@param	ポジション
@param	移動速度
@param	何色か判定用Tag
*/
CrystalDefaultEffect::CrystalDefaultEffect(const Vector3& _pos, const Vector3& _velocity, CrystalColor _crystalColor)
	: ParticleEffectBase(_pos, _velocity, 100, "Assets/Effect/Particle_Soft.png", true)
	, AddScale(2.0f)
	, AddAlpha(0.005f)
	, SubAlpha(0.002f)
	, MaxAlphaValue(0.6f)
{
	// メンバー変数の初期化
	scale = 0.0f;
	alpha = 0.0f;
	speed = 20.0f;
	inFlag = true;
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
CrystalDefaultEffect::~CrystalDefaultEffect()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void CrystalDefaultEffect::UpdateGameObject(float _deltaTime)
{
	// 生存時間のカウントダウン
	ParticleEffectBase::LifeCountDown();

	// ライフカウントが0以上になったら
	if (lifeCount > 0)
	{
		// フェードイン処理
		FadeInProcess();

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

/*
@fn フェードイン関数
*/
void CrystalDefaultEffect::FadeInProcess()
{
	// フェードインフラグがtrueだったら
	if (inFlag == true)
	{
		// alpha値に定数を足す
		alpha += AddAlpha;
		// alpha値の最大定数に到達したら
		if (alpha >= MaxAlphaValue)
		{
			// フェードインフラグをfalseに
			inFlag = false;
		}
	}
}