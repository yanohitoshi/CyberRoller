#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class MusicComponent;
class SoundEffectComponent;

/*
@file StageSelectSceneSoundManager.h
@brief ステージ選択シーンのサウンドを管理するクラス
*/
class StageSelectSceneSoundManager :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	*/
	StageSelectSceneSoundManager();

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~StageSelectSceneSoundManager()override;

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn 入力を引数で受け取る更新関数
	@brief 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
	@param	_keyState 入力情報
	*/
	void GameObjectInput(const InputState& _keyState);

private:

	// オーナークラスのポインタ
	BaseScene* owner;

	// BGMを管理するクラス
	MusicComponent* bgm;
	SoundEffectComponent* changeSelectSceneSound;
	SoundEffectComponent* sceneDecisionSound;

	// アナログスティックによる選択シーン変更が可能かどうか
	bool isAnalogStickSelect;
	// アナログスティックによる選択の再使用可能になるまでのカウントを数える
	int selectCount;

	// 決定ボタンが押されたかどうか
	bool isPushDecisionSceneButton;
	// 入力が利用可能かどうか
	bool isAvailableSelectInput;

	// stage決定時のサウンドがなり終わったかどうか
	bool isPlayDecisionSound;

	// デッドスペース定数
	const float InputDeadSpace;
	// 連続でステージの選択が切り替わらないようにするための待ち時間定数
	const int SelectDelay;

public:

	/*
	@brief	stage決定時のサウンドがなり終わったかどうかを取得
	@return	isEndDecisionSound stage決定時のサウンドの再生が終わったかどうか
	*/
	bool GetIsPlayDecisionSound() { return isPlayDecisionSound; }
};

