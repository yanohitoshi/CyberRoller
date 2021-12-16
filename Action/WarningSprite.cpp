//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "WarningSprite.h"
#include "GraphicsResourceManager.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"
#include "SoundEffectComponent.h"

/*
@fn コンストラクタ
@brief	コンストラクタ
@param	親となるCountDownFont型ポインタ
*/
WarningSprite::WarningSprite(CountDownFont* _owner)
	:GameObject(false, Tag::UI)
	, ChangeFadeInValue(0.1f)
	, ChangeFadeOutValue(0.9f)
	, FadeValue(0.01f)
{
	// 変数の初期化
	owner = _owner;
	alpha = 0.1f;
	fadeinCount = 0;
	fadeFlag = true;
	isPlaySound = true;

	// ポジションをセット
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// SpriteComponentの初期化
	sprite = new SpriteComponent(this, false);
	Texture* tex = GRAPHICS_RESOURCE->CreateTexture("Assets/sprite/information/warning.png");
	sprite->SetTexture(tex);
	sprite->SetVisible(true);
	sprite->SetAlpha(alpha);

	// サウンドエフェクトを生成
	soundEffect = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/Time/Warning.wav");
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
WarningSprite::~WarningSprite()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void WarningSprite::UpdateGameObject(float _deltaTime)
{
	// サウンドを再生する条件を判定
	if (owner->GetWarningFlag() && isPlaySound)
	{
		// サウンドを再生
		soundEffect->Play();
		// 再生しない状態にする
		isPlaySound = false;
	}

	// countが2以下かつownerのフラグがtrueの時
	if (fadeinCount <= 2 && owner->GetWarningFlag())
	{
		// 状態チェックと実際の処理
		CheckFadeInOutProcess();
	}
	else if (fadeinCount >= 3)	// countが3以上になったらalpha値が0になるまでout
	{
		// サウンドが鳴っていたら
		if (soundEffect->IsPlaying())
		{
			// サウンドを停止する
			soundEffect->Stop();
		}
		// 最後のフェードアウト処理
		LastFadeOutProcess();
	}

	// alpha値をセット
	sprite->SetAlpha(alpha);
}

/*
@fn フェードインアウトの状態を見る関数
*/
void WarningSprite::CheckFadeInOutProcess()
{
	// フェードインアウト処理
	FadeInOutProcess();
	// フェードインアウト切り替え処理
	ChangeFadeProcess();

}

/*
@fn フェードインアウト処理関数
*/
void WarningSprite::FadeInOutProcess()
{
	// fadeFlagがtrueだったらfadein
	if (fadeFlag == true)
	{
		alpha += FadeValue;
	}
	else if (fadeFlag == false)		// fadeFlagがfalseだったらfadeout
	{
		alpha -= FadeValue;
	}
}

/*
@fn 最後のフェードアウト処理関数
*/
void WarningSprite::LastFadeOutProcess()
{
	// alpha値が0.0f以上だったら
	if (alpha >= 0.0f)
	{
		// 値を引く
		alpha -= FadeValue;
	}
}

/*
@fn フェードインアウトの切り替え処理関数
*/
void WarningSprite::ChangeFadeProcess()
{
	// alpha値を見てin/outを切り替え
	if (alpha <= ChangeFadeInValue)
	{
		// フラグをin状態であるtrueに変更
		fadeFlag = true;
	}
	else if (alpha >= ChangeFadeOutValue)
	{
		// フラグをout状態であるfalseに変更
		fadeFlag = false;
		++fadeinCount;
	}
}