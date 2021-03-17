#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include <SDL_mixer.h>
#include <iostream>

// 未実装
/*
@file Music.h
@brief Music(BGM)の読み込み・再生・停止を行う
*/
class Music
{
public:
    
    /*
    @fn コンストラクタ
    @brief ミュージッククラスの生成を行う
    */
    Music();
    
    /*
    @fn デストラクタ
    @brief ミュージックの解放を行う
    */
    ~Music();
    
    /*
    @fn 再生関数
    @brief ミュージックを再生を行う
    */
    void Play();

    /*
    @fn フェードイン関数
    @brief ミュージックのフェードインを行う
    */
    void FadeInMusic(int fadeInTime);

    /*
    @fn 再生関数
    @brief ミュージック読み込みを行う
    @param fileName　読み込むミュージックファイルのパス
    @return bool true 読み込み成功 : false 読み込み失敗
    */
    bool LoadMusic(const std::string& fileName);

    /*
    @fn 停止関数
    @brief ミュージックを停止する
    */
    static void Stop();
    
    /*
    @fn フェードアウト関数
    @brief 再生中のミュージックをフェードアウトする
    */
    static void FadeOutMusic(int fadeOutTime);
    
    /*
    @fn 再生状態確認関数
    @brief ミュージックが再生中かどうかフラグの取得
    @return bool true 再生中 : false 非再生中
    */
    static bool IsPlaying();

private:

    // 音源データ
    Mix_Music* mMusic;

};

