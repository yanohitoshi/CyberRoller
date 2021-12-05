//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "FirstSceneSoundManager.h"
#include "AudioResourceManager.h"
#include "MusicComponent.h"
#include "SoundEffectComponent.h"
#include "BaseScene.h"

/*
@fn コンストラクタ
@param 親クラスのシーンクラスのポインタ
*/
FirstSceneSoundManager::FirstSceneSoundManager(BaseScene* _owner)
	: GameObject(false, Tag::AUDIO)
{
	// 変数を初期化
	owner = _owner;
	isCountDownPlay = true;
	isbgmChanged = false;
	isPlayContinue = true;
	isPlayGameEnd = true;

	// BGM生成
	bgm = new MusicComponent(this, "Assets/Sound/Bgm/Game/First.wav");
	gameOverBgm = new MusicComponent(this, "Assets/Sound/Bgm/TimeUp/TimeUp.wav");

	// サウンドエフェクト生成
	countDown = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/CountDown/CountDown.wav");
	continueSound = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/Continue/Continue.wav");
	gameEnd = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/GameOver/GameEnd.wav");

}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
FirstSceneSoundManager::~FirstSceneSoundManager()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void FirstSceneSoundManager::UpdateGameObject(float _deltaTime)
{
	// カウントダウン音を再生する状態だったら
	if (!owner->GetStartScene() && isCountDownPlay)
	{
		// カウントダウン音を再生する
		countDown->Play();
		// カウントダウン音を再生するかをfalseに切り替える
		isCountDownPlay = false;
	}

	// ゲームBGMを再生するかを判定
	bool isPlayBgm = !isCountDownPlay && !owner->GetIsSceneClear() &&!owner->GetIsTimeOver();

	// 再生する状態かつ再生されて居なかったら
	if (isPlayBgm && !bgm->IsPlaying())
	{
		// ゲームBGM再生する
		bgm->Play();
	}

	// シーンをクリアしたら
	if (owner->GetIsSceneClear())
	{
		// ゲームBGM停止する
		bgm->Stop();
	}

	// タイムオーバーになってBGMが切り替わっていなかったら
	if (owner->GetIsTimeOver() && !isbgmChanged)
	{
		// 再生されていたら
		if (bgm->IsPlaying())
		{
			// ゲームBGMを停止
			bgm->Stop();
		}

		// ゲームオーバーBGMを再生
		gameOverBgm->Play();
		// 切り替えフラグをfalseにする
		isbgmChanged = true;
	}

	// コンティニューが選択されていたら
	if (owner->GetIsContinueFlag() && isPlayContinue)
	{
		// コンティニューサウンドエフェクトを再生
		continueSound->Play();
		isPlayContinue = false;
	}

	// ゲーム終了が選択されていたら
	if (owner->GetIsEndFlag() && isPlayGameEnd)
	{
		gameEnd->Play();
		isPlayGameEnd = false;
	}
}