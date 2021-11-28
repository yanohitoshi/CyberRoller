#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "SDL.h"
#include <unordered_map>    

// シングルトンなのでインスタンスのgetterを静的領域にdefineで定義
#define AUDIO_RESOURCE AudioResourceManager::GetInstance()

// クラスの前方宣言
class Sound;
class Music;

/*
@file AudioResourceManager.h
@brief Audioの管理を行う
*/
class AudioResourceManager
{
public:

    /*
    @brief  インスタンスを取得する
    @return AudioManagerクラスのインスタンス
    */

    static AudioResourceManager* GetInstance() { return audioResource; }

    /*
    @brief  インスタンスを作成する
    */
    static void CreateInstance();

    /*
    @brief  インスタンスを削除する
    */
    static void DeleteInstance();

    /*
    @fn 読み込み関数(サウンド)
    @brief サウンドの読み込みを行う
    @param fileName　読み込むサウンドファイルのパス
    */
    Sound* AddSound(const std::string& fileName);
        
    /*
    @fn 削除関数(サウンド)
    @brief サウンドの削除を行う
    @param fileName　削除するサウンドファイルのパス
    */
    void RemoveSound(const std::string& fileName);
        
    /*
    @fn 読み込み関数(ミュージック)
    @brief ミュージックの読み込みを行う
    @param fileName　読み込むミュージックファイルのパス
    */
    Music* AddMusic(const std::string& fileName);
    
    /*
    @fn 削除関数(ミュージック)
    @brief ミュージックの削除を行う
    @param fileName　削除するミュージックファイルのパス
    */
    void RemoveMusic(const std::string& fileName);
        
    /*
    @fn 終了処理関数
    @brief 生成したMusic・Soundの解放処理を行う
    */
    void ShutDown();

private:

    /*
    @fn コンストラクタ
    */
    AudioResourceManager();
    
    /*
    @fn デストラクタ
    @brife 保持している全てのSound・Musicを解放する
    */
    ~AudioResourceManager();

    //自分のインスタンス
    static AudioResourceManager* audioResource;

    // ファイルネームをkeyとして持つSoundクラスとMusicクラスの連想可変長配列
    // 読み込んだサウンドやミュージックのデータを保持する
    std::unordered_map<std::string, class Sound*> sounds;
    std::unordered_map<std::string, class Music*> musics;

};