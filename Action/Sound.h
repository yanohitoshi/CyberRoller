#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include <SDL_mixer.h>
#include <iostream>

/*
@file Sound.h
@brief Sound(SE)の読み込み・再生・停止を行う
*/
class Sound
{
public:
    
    /*
    @fn コンストラクタ
    @brief サウンドクラスの生成を行う
    */
    Sound();

    /*
    @fn デストラクタ
    @brief サウンドの解放を行う
    */
    ~Sound();

    /*
    @fn 再生関数
    @brief サウンドを再生する
    */
    void Play();

    /*
    @fn 停止関数
    @brief サウンドを停止する
    */
    void Stop();

    /*
    @fn サウンドファイル読み込み関数
    @brief サウンドファイルを読み込む
    @param fileName　読み込むサウンドファイルのパス
    @return bool true 読み込み成功 : false 読み込み失敗
    */
    bool LoadSound(const std::string& fileName);

    /*
    @fn 再生状態確認関数
    @brief サウンドが再生中かどうかフラグの取得
    @return bool true 再生中 : false 非再生中
    */
    bool IsPlaying();

private:

    // サウンドデータ
    Mix_Chunk* chunk;

    // 再生チャンネル
    int channel;
};