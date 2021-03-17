#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include <SDL_mixer.h>
#include <iostream>

// ������
/*
@file Music.h
@brief Music(BGM)�̓ǂݍ��݁E�Đ��E��~���s��
*/
class Music
{
public:
    
    /*
    @fn �R���X�g���N�^
    @brief �~���[�W�b�N�N���X�̐������s��
    */
    Music();
    
    /*
    @fn �f�X�g���N�^
    @brief �~���[�W�b�N�̉�����s��
    */
    ~Music();
    
    /*
    @fn �Đ��֐�
    @brief �~���[�W�b�N���Đ����s��
    */
    void Play();

    /*
    @fn �t�F�[�h�C���֐�
    @brief �~���[�W�b�N�̃t�F�[�h�C�����s��
    */
    void FadeInMusic(int fadeInTime);

    /*
    @fn �Đ��֐�
    @brief �~���[�W�b�N�ǂݍ��݂��s��
    @param fileName�@�ǂݍ��ރ~���[�W�b�N�t�@�C���̃p�X
    @return bool true �ǂݍ��ݐ��� : false �ǂݍ��ݎ��s
    */
    bool LoadMusic(const std::string& fileName);

    /*
    @fn ��~�֐�
    @brief �~���[�W�b�N���~����
    */
    static void Stop();
    
    /*
    @fn �t�F�[�h�A�E�g�֐�
    @brief �Đ����̃~���[�W�b�N���t�F�[�h�A�E�g����
    */
    static void FadeOutMusic(int fadeOutTime);
    
    /*
    @fn �Đ���Ԋm�F�֐�
    @brief �~���[�W�b�N���Đ������ǂ����t���O�̎擾
    @return bool true �Đ��� : false ��Đ���
    */
    static bool IsPlaying();

private:

    // �����f�[�^
    Mix_Music* mMusic;

};

