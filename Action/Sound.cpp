//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Sound.h"

/*
@fn コンストラクタ
@brief サウンドクラスの生成を行う
*/
Sound::Sound()
    :chunk(nullptr)
    , channel(-1)
{
}

/*
@fn サウンドファイル読み込み関数
@brief サウンドファイルを読み込む
@param fileName　読み込むサウンドファイルのパス
@return bool true 読み込み成功 : false 読み込み失敗
*/
bool Sound::LoadSound(const std::string& fileName)
{
    chunk = Mix_LoadWAV(fileName.c_str());
    return chunk != nullptr;
}

/*
@fn 再生状態確認関数
@brief サウンドが再生中かどうかフラグの取得
@return bool true 再生中 : false 非再生中
*/
bool Sound::IsPlaying()
{
    return channel >= 0 && Mix_Playing(channel);
}

void Sound::SetChannelVolume(int _volume)
{
    Mix_Volume(channel, _volume);
}

/*
@fn デストラクタ
@brief サウンドの解放を行う
*/
Sound::~Sound()
{
    Mix_FreeChunk(chunk);//読み取ったサウンドの開放
}

/*
@fn 再生関数
@brief サウンドを再生する
*/
void Sound::Play()
{
    channel = Mix_PlayChannel(-1, chunk, 0);
}

/*
@fn 停止関数
@brief サウンドを停止する
*/
void Sound::Stop()
{
    if (channel == -1)
    {
        return;
    }

    if (Mix_Playing(channel))
    {
        Mix_HaltChannel(channel);
    }
    channel = -1;
}