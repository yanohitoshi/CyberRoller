#pragma once
#include "GameObject.h"

class MusicComponent;

class TitleSceneSoundManager :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	*/
	TitleSceneSoundManager();

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~TitleSceneSoundManager()override;

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// Meshを管理するクラス
	MusicComponent* bgm;
};

