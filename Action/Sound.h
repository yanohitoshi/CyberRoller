#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include <SDL_mixer.h>
#include <iostream>

/*
@file Sound.h
@brief Sound(SE)�̓ǂݍ��݁E�Đ��E��~���s��
*/
class Sound
{
public:
    
    /*
    @fn �R���X�g���N�^
    @brief �T�E���h�N���X�̐������s��
    */
    Sound();

    /*
    @fn �f�X�g���N�^
    @brief �T�E���h�̉�����s��
    */
    ~Sound();

    /*
    @fn �Đ��֐�
    @brief �T�E���h���Đ�����
    */
    void Play();

    /*
    @fn ��~�֐�
    @brief �T�E���h���~����
    */
    void Stop();

    /*
    @fn �T�E���h�t�@�C���ǂݍ��݊֐�
    @brief �T�E���h�t�@�C����ǂݍ���
    @param fileName�@�ǂݍ��ރT�E���h�t�@�C���̃p�X
    @return bool true �ǂݍ��ݐ��� : false �ǂݍ��ݎ��s
    */
    bool LoadSound(const std::string& fileName);

    /*
    @fn �Đ���Ԋm�F�֐�
    @brief �T�E���h���Đ������ǂ����t���O�̎擾
    @return bool true �Đ��� : false ��Đ���
    */
    bool IsPlaying();

private:

    // �T�E���h�f�[�^
    Mix_Chunk* chunk;

    // �Đ��`�����l��
    int channel;
};