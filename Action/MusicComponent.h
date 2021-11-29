#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "AudioComponent.h"

// classの前方宣言
class Music;

/*
@file MusicComponent.h
@brief BGMを更新するクラス
*/
class MusicComponent :
    public AudioComponent
{
public:

    /*
    @brief	コンストラクタ
    @param	アタッチするゲームオブジェクトのポインタ
    @param	読み込むサウンドファイルのパス
    @param	コンポーネントの更新順番（数値が小さいほど早く更新される）
    */
	MusicComponent(GameObject* _owner, const std::string& _fileName, int _updateOrder = 100);

	/*
	@fn デストラクタ
	@brief  componentの削除を行う
	*/
	~MusicComponent()override;

    /*
    @fn フェードイン再生関数(ミュージック)
    @brief ミュージックのフェードイン再生を行う
    @param fadeInTime　フェードインにかける時間
    */
    void PlayFadeIn(int _fadeInTime);

    /*
    @fn 再生関数(ミュージック)
    @brief ミュージックを再生を行う
    */
    void Play();

    /*
    @fn フェードアウト関数(ミュージック)
    @brief 再生中のミュージックのフェードアウトを行う
    @param fadeOutTime　フェードアウトにかける時間
    */
    void FadeOut(int _fadeOutTime);

    /*
    @fn 停止関数(ミュージック)
    @brief ミュージックを停止を行う
    */
    void Stop();

    /*
    @fn 再生状態確認関数(ミュージック)
    @brief ミュージックが再生中かどうかフラグの取得
    @return bool true 再生中 : false 非再生中
    */
    bool IsPlaying();

private:

    // 自分が担当するMusicクラスのポインタ
	Music* myMusic;
};