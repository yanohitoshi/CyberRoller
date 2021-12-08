#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class MusicComponent;
class SoundEffectComponent;

/*
@file TutorialSceneSoundManager .h
@brief チュートリアルステージシーンのサウンドを管理するクラス
*/
class TutorialSceneSoundManager :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param 親クラスのシーンクラスのポインタ
	*/
	TutorialSceneSoundManager(BaseScene* _owner);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~TutorialSceneSoundManager()override;

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// オーナークラスのポインタ
	BaseScene* owner;

	// BGMを管理するクラス
	MusicComponent* bgm;
	SoundEffectComponent* countDown;

	// カウントダウン音を鳴らすかどうか
	bool isCountDownPlay;
};

