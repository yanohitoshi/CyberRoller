/*�������Ȃ̂Ŏg�p���Ă��܂���*/

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Sound.h"

Sound::Sound()
    :chunk(nullptr)
    , channel(-1)
{
}

bool Sound::LoadSound(const std::string& fileName)
{
    chunk = Mix_LoadWAV(fileName.c_str());
    return chunk != nullptr;
}

bool Sound::IsPlaying()
{
    return channel >= 0 && Mix_Playing(channel);
}


Sound::~Sound()
{
    Mix_FreeChunk(chunk);//�ǂݎ�����T�E���h�̊J��
}

void Sound::Play()
{
    channel = Mix_PlayChannel(-1, chunk, 0);
}

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