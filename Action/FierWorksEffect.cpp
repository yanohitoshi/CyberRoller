//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "FierWorksEffect.h"
#include "ParticleComponent.h"
#include "CrystalEffectManager.h"

/*
@fn コンストラクタ
@param	ポジション
@param	移動速度
@param	何色か判定用Tag
*/
FierWorksEffect::FierWorksEffect(const Vector3& _pos, const Vector3& _velocity, CrystalColor _crystalColor)
	: ParticleEffectBase(_pos, _velocity, 210, "Assets/Effect/Particle_Soft.png",true, true)
	, FadeInAddScale(2.0f)
	, FadeOutAddScale(5.0f)
	, MaxAlpha(0.9f)
	, AddAlpha(0.05f)
	, SubAlpha(0.001f)
	, SubSpeed(1.0f)
	, VelocityAtFadeOut(40.0f)
	, ChangeFadeOutTime(190)
	, WhiteValue(Vector3(0.9f, 0.9f, 0.9f))
	, RedValue(Vector3(1.0f, 0.5f, 0.5f))
	, BlueValue(Vector3(0.5f, 0.5f, 1.0f))
	, GreenValue(Vector3(0.5f, 1.0f, 0.5f))
{
	// メンバー変数の初期化
	scale = 2.0f;
	alpha = 0.1f;
	speed = 200.0f;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);
	// 最初はフェードイン状態に初期化
	inFlag = true;

	// マネージャークラスの色情報を参照して色を設定
	if (_crystalColor == CrystalColor::WHITE)
	{
		particleComponent->SetColor(WhiteValue);
	}
	else if (_crystalColor == CrystalColor::RED)
	{
		particleComponent->SetColor(RedValue);
	}
	else if (_crystalColor == CrystalColor::BLUE)
	{
		particleComponent->SetColor(BlueValue);
	}
	else if (_crystalColor == CrystalColor::GREEN)
	{
		particleComponent->SetColor(GreenValue);
	}
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
FierWorksEffect::~FierWorksEffect()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void FierWorksEffect::UpdateGameObject(float _deltaTime)
{
	// 生存時間のカウントダウン
	ParticleEffectBase::LifeCountDown();

	// ライフカウントがフェードイン・アウトの切り替えタイミングに到達していなかったら
	if (lifeCount > ChangeFadeOutTime)
	{
		FadeInProcess();

		// 定数を足して拡大
		scale += FadeInAddScale;

		// scale値をセット
		particleComponent->SetScale(scale);
		// alpha値をセット
		particleComponent->SetAlpha(alpha);

		// ポジションに速度を追加
		position += velocity * speed * _deltaTime;
		// ポジションを更新
		SetPosition(position);

	}
	else if (lifeCount <= ChangeFadeOutTime) // 切り替える値に到達していたら
	{
		// フェードアウト用定数を足して拡大
		scale += FadeOutAddScale;
		// 定数を引いて透過
		alpha -= SubAlpha;

		// x,y軸を0.0fに固定
		velocity.x = 0.0f;
		velocity.y = 0.0f;

		// 速度をチェック
		ChackSpeedProcess();

		// scale値をセット
		particleComponent->SetAlpha(alpha);
		// alpha値をセット
		particleComponent->SetScale(scale);

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
void FierWorksEffect::FadeInProcess()
{
	// フェードイン状態だったら
	if (inFlag == true)
	{
		// alpha値に定数を足す
		alpha += AddAlpha;

		// alpha値が最大値に到達したら
		if (alpha >= MaxAlpha)
		{
			// フェードインフラグをfalseに
			inFlag = false;
		}
	}

}

/*
@fn 速度抑制関数
*/
void FierWorksEffect::ChackSpeedProcess()
{
	// 速度が定数より大きかったらだったら
	if (speed > VelocityAtFadeOut)
	{
		// 減速
		speed -= SubSpeed;

		// 速度が定数以下だったら
		if (speed <= VelocityAtFadeOut)
		{
			// 定数を代入
			speed = VelocityAtFadeOut;
		}
	}

}
