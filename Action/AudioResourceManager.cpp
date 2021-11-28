//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "AudioResourceManager.h"
#include "Music.h"
#include "Sound.h"

AudioResourceManager* AudioResourceManager::audioResource = nullptr;

/*
@fn コンストラクタ
*/
AudioResourceManager::AudioResourceManager()
{
}

/*
@fn デストラクタ
@brife 保持している全てのSound・Musicを解放する
*/
AudioResourceManager::~AudioResourceManager()
{
    if (sounds.size() > 0 || musics.size() > 0)
    {
        ShutDown();
    }
}

/*
@brief  インスタンスを作成する
*/
void AudioResourceManager::CreateInstance()
{
    if (audioResource == nullptr)
    {
        audioResource = new AudioResourceManager();
    }
}

/*
@brief  インスタンスを削除する
*/
void AudioResourceManager::DeleteInstance()
{
    if (audioResource != nullptr)
    {
        delete audioResource;
        audioResource = nullptr;
    }
}

/*
@fn 読み込み関数(サウンド)
@brief サウンドの読み込みを行う
@param fileName　読み込むサウンドファイルのパス
*/
Sound* AudioResourceManager::AddSound(const std::string& fileName)
{
    Sound* sound = nullptr;//サウンドクラスのポインタ(初期化)
    auto iter = sounds.find(fileName);//ファイル名の検索
    // サウンドファイル登録されているか？
    if (iter != sounds.end())//サウンド検索が成功したのか
    {
        sound = iter->second;//サウンドが見つかった
    }
    else
    {
        // 登録なかったら新規サウンド読み込み
        sound = new Sound();
        if (sound->LoadSound(fileName))
        {
            sounds.emplace(fileName, sound);//実質mSounds[fileName] = sound;をしている
        }
        else
        {
            printf("%s 読み込み失敗\n", fileName.c_str());
            delete sound;
            sound = nullptr;
        }
    }

    return sound;
}

/*
@fn 削除関数(サウンド)
@brief サウンドの削除を行う
@param fileName　削除するサウンドファイルのパス
*/
void AudioResourceManager::RemoveSound(const std::string& fileName)
{
    // サウンドファイルを削除
    auto iter = sounds.find(fileName);
    if (iter != sounds.end())
    {
        printf("release: %s\n", iter->first.c_str());
        delete iter->second;
        sounds.erase(iter);
    }
}

/*
@fn 読み込み関数(ミュージック)
@brief ミュージックの読み込みを行う
@param fileName　読み込むミュージックファイルのパス
*/
Music* AudioResourceManager::AddMusic(const std::string& fileName)
{
    Music* music = nullptr;//初期化
    auto iter = musics.find(fileName);//ファイル名の検索
    //ミュージックファイル登録されているか？
    if (iter != musics.end())//ミュージック検索が成功したのか
    {
        music = iter->second;//ミュージックが見つかった
    }
    else
    {
        //登録がなかったら新規ミュージック読み込み
        music = new Music();
        if (music->LoadMusic(fileName))
        {
            musics.emplace(fileName, music);
        }
        else
        {
            printf("%s読み込み失敗\n", fileName.c_str());
            delete music;
            music = nullptr;
        }
    }
    return music;
}

/*
@fn 削除関数(ミュージック)
@brief ミュージックの削除を行う
@param fileName　削除するミュージックファイルのパス
*/
void AudioResourceManager::RemoveMusic(const std::string& fileName)
{
    //ミュージックファイルを削除
    auto iter = musics.find(fileName);
    if (iter != musics.end())
    {
        printf("release: %s\n", iter->first.c_str());
        delete iter->second;
        musics.erase(iter);
    }
}

/*
@fn 終了処理関数
@brief 生成したMusic・Soundの解放処理を行う
*/
void AudioResourceManager::ShutDown()
{
    //サウンド破棄
    for (auto i : sounds)
    {
        printf("release : %s\n", i.first.c_str());
        delete i.second;
    }
    sounds.clear();
    //ミュージック破棄コードをここに書く
    for (auto i : musics)
    {
        printf("release : %s\n", i.first.c_str());
        delete i.second;
    }
    musics.clear();
}