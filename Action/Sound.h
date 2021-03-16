#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include <SDL_mixer.h>
#include <iostream>

// ������
class Sound
{
public:
    Sound();
    ~Sound();
    void          Play();       // �Đ�
    void          Stop();       // �X�g�b�v
    bool          LoadSound(const std::string& fileName); // �T�E���h�t�@�C���ǂݍ���
    /*
    @fn �Đ�����
    */
    bool IsPlaying();  // ���ݍĐ������H

private:

    // �T�E���h�f�[�^
    Mix_Chunk* mChunk;
    // �Đ��`�����l��
    int mChannel;

};

