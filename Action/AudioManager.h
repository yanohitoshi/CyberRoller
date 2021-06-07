
/*未実装なので使用していません*/

#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "SDL.h"
#include <unordered_map>    

// シングルトンなのでインスタンスのgetterを静的領域にdefineで定義
#define AUDIO AudioManager::GetInstance()

// クラスの前方宣言
class Sound;
class Music;

/*
@file AudioManager.h
@brief Audioの管理を行う
*/
class AudioManager
{
public:

    /*
    @brief  インスタンスを取得する
    @return AudioManagerクラスのインスタンス
    */

    static AudioManager* GetInstance() { return audio; }

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
    Sound* GetSound(const std::string& fileName);
    
    /*
    @fn 削除関数(サウンド)
    @brief サウンドの削除を行う
    @param fileName　削除するサウンドファイルのパス
    */
    void RemoveSound(const std::string& fileName);
    
    /*
    @fn 再生関数(サウンド)
    @brief サウンドの再生を行う
    @param fileName　再生するサウンドファイルのパス
    */
    void PlaySound(const std::string& fileName);
    
    /*
    @fn 停止関数(サウンド)
    @brief サウンドの停止を行う
    @param fileName　停止するサウンドファイルのパス
    */
    void StopSound(const std::string& fileName);
    
    /*
    @fn 再生状態確認関数(サウンド)
    @brief 指定したサウンドが再生中かどうかフラグの取得
    @param fileName　指定するサウンドファイルのパス
    @return bool true 再生中 : false 非再生中
    */
    bool IsPlayingSound(const std::string& fileName);
    
    /*
    @fn 読み込み関数(ミュージック)
    @brief ミュージックの読み込みを行う
    @param fileName　読み込むミュージックファイルのパス
    */
    Music* GetMusic(const std::string& fileName);
    
    /*
    @fn 削除関数(ミュージック)
    @brief ミュージックの削除を行う
    @param fileName　削除するミュージックファイルのパス
    */
    void RemoveMusic(const std::string& fileName);
    
    /*
    @fn フェードイン再生関数(ミュージック)
    @brief ミュージックのフェードイン再生を行う
    @param fileName　フェードイン再生するミュージックファイルのパス
    */
    void PlayFadeInMusic(const std::string& fileName, int fadeInTime);
    
    /*
    @fn 再生関数(ミュージック)
    @brief ミュージックを再生を行う
    @param fileName　再生するミュージックファイルのパス
    */
    void PlayMusic(const std::string& fileName);
    
    /*
    @fn フェードアウト関数(ミュージック)
    @brief 再生中のミュージックのフェードアウトを行う
    @param fadeOutTime　フェードアウトにかける時間
    */
    void FadeOutMusic(int fadeOutTime);

    /*
    @fn 停止関数(ミュージック)
    @brief ミュージックを停止を行う
    */
    void StopMusic();
    
    /*
    @fn 再生状態確認関数(ミュージック)
    @brief ミュージックが再生中かどうかフラグの取得
    @return bool true 再生中 : false 非再生中
    */
    bool IsPlayingMusic();
    
    /*
    @fn 終了処理関数
    @brief 生成したMusic・Soundの解放処理を行う
    */
    void ShutDown();

private:

    /*
    @fn コンストラクタ
    */
    AudioManager();
    
    /*
    @fn デストラクタ
    @brife 保持している全てのSound・Musicを解放する
    */
    ~AudioManager();

    //自分のインスタンス
    static AudioManager* audio;

    // ファイルネームをkeyとして持つSoundクラスとMusicクラスの連想可変長配列
    // 読み込んだサウンドやミュージックのデータを保持する
    std::unordered_map<std::string, class Sound*> mSounds;
    std::unordered_map<std::string, class Music*> mMusics;

};

