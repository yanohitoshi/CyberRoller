
/*未実装なので使用していません*/

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "AudioManager.h"
#include "Music.h"
#include "Sound.h"

AudioManager* AudioManager::audio = nullptr;

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
    if (sounds.size() > 0 || musics.size() > 0)
    {
        ShutDown();
    }
}


/*
@brief  インスタンスを作成する
*/
void AudioManager::CreateInstance()
{
    if (audio == nullptr)
    {
        audio = new AudioManager();
    }
}

/*
@brief  インスタンスを削除する
*/
void AudioManager::DeleteInstance()
{
    if (audio != nullptr)
    {
        delete audio;
        audio = nullptr;
    }
}

// サウンド取得
Sound* AudioManager::GetSound(const std::string& fileName)
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

void AudioManager::RemoveSound(const std::string& fileName)
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

void AudioManager::PlaySound(const std::string& fileName)
{
    //サウンド鳴らす
    sounds[fileName]->Play();
}

void AudioManager::StopSound(const std::string& fileName)
{
    sounds[fileName]->Stop();
}

bool AudioManager::IsPlayingSound(const std::string& fileName)
{
    return sounds[fileName]->IsPlaying();
}

Music* AudioManager::GetMusic(const std::string& fileName)
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
    return nullptr;
}

void AudioManager::RemoveMusic(const std::string& fileName)
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

void AudioManager::PlayFadeInMusic(const std::string& fileName, int fadeInTime)
{
    musics[fileName]->FadeInMusic(fadeInTime);
}

void AudioManager::PlayMusic(const std::string& fileName)
{
    //ミュージックを鳴らす
    musics[fileName]->Play();
}

void AudioManager::FadeOutMusic(int fadeOutTime)
{
    Music::FadeOutMusic(fadeOutTime);
}

void AudioManager::StopMusic()
{
    Music::Stop();
}

bool AudioManager::IsPlayingMusic()
{
    return Music::IsPlaying();
}

void AudioManager::ShutDown()
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