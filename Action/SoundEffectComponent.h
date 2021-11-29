#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "AudioComponent.h"

// classの前方宣言
class Sound;

/*
@file SoundEffectComponent.h
@brief サウンドエフェクトを更新するクラス
*/
class SoundEffectComponent :
    public AudioComponent
{
public:

	/*
	@fn コンストラクタ
	@param	アタッチするゲームオブジェクトのポインタ
    @param	サウンドのファイルパス
	@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
	*/
	SoundEffectComponent(GameObject* _owner, const std::string& _fileName,int _updateOrder = 100);

	/*
	@fn デストラクタ
	@brief  componentの削除を行う
	*/
	~SoundEffectComponent()override;

    /*
    @fn 再生関数(サウンド)
    @brief サウンドの再生を行う
    */
    void Play();

    /*
    @fn 停止関数(サウンド)
    @brief サウンドの停止を行う
    */
    void Stop();

    /*
    @fn 再生状態確認関数(サウンド)
    @brief 指定したサウンドが再生中かどうかフラグの取得
    @return bool true 再生中 : false 非再生中
    */
    bool IsPlaying();

private:

    // 自分が担当するSoundクラスのポインタ
	Sound* mySound;
};