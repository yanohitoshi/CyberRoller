//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TutorialSceneSoundManager.h"
#include "AudioResourceManager.h"
#include "MusicComponent.h"
#include "BaseScene.h"

/*
@fn コンストラクタ
@param 親クラスのシーンクラスのポインタ
*/
TutorialSceneSoundManager::TutorialSceneSoundManager(BaseScene* _owner)
	: GameObject(false, Tag::AUDIO)
{
	// 変数初期化
	owner = _owner;
	isCountDownPlay = true;

	// BGMを生成
	bgm = new MusicComponent(this, "Assets/Sound/Bgm/Tutorial/Tutorial.wav");
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
TutorialSceneSoundManager::~TutorialSceneSoundManager()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void TutorialSceneSoundManager::UpdateGameObject(float _deltaTime)
{
	if (!bgm->IsPlaying())
	{
		bgm->Play();
	}

	if (owner->GetIsSceneClear())
	{
		bgm->Stop();
	}
}