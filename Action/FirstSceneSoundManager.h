#pragma once
#include "GameObject.h"

class MusicComponent;
class SoundEffectComponent;

class FirstSceneSoundManager :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	*/
	FirstSceneSoundManager(BaseScene* _owner);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~FirstSceneSoundManager()override;

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	BaseScene* owner;

	// BGMを管理するクラス
	MusicComponent* bgm;
	SoundEffectComponent* countDown;

	// カウントダウン音を鳴らすかどうか
	bool isCountDownPlay;

};

