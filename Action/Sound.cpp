//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Sound.h"

/*
@fn �R���X�g���N�^
@brief �T�E���h�N���X�̐������s��
*/
Sound::Sound()
    :chunk(nullptr)
    , channel(-1)
{
}

/*
@fn �T�E���h�t�@�C���ǂݍ��݊֐�
@brief �T�E���h�t�@�C����ǂݍ���
@param fileName�@�ǂݍ��ރT�E���h�t�@�C���̃p�X
@return bool true �ǂݍ��ݐ��� : false �ǂݍ��ݎ��s
*/
bool Sound::LoadSound(const std::string& fileName)
{
    chunk = Mix_LoadWAV(fileName.c_str());
    return chunk != nullptr;
}

/*
@fn �Đ���Ԋm�F�֐�
@brief �T�E���h���Đ������ǂ����t���O�̎擾
@return bool true �Đ��� : false ��Đ���
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
@fn �f�X�g���N�^
@brief �T�E���h�̉�����s��
*/
Sound::~Sound()
{
    Mix_FreeChunk(chunk);//�ǂݎ�����T�E���h�̊J��
}

/*
@fn �Đ��֐�
@brief �T�E���h���Đ�����
*/
void Sound::Play()
{
    channel = Mix_PlayChannel(-1, chunk, 0);
}

/*
@fn ��~�֐�
@brief �T�E���h���~����
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