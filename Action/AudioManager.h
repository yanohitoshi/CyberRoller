
/*�������Ȃ̂Ŏg�p���Ă��܂���*/

#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SDL.h"
#include <unordered_map>    

// �V���O���g���Ȃ̂ŃC���X�^���X��getter��ÓI�̈��define�Œ�`
#define AUDIO AudioManager::GetInstance()

// �N���X�̑O���錾
class Sound;
class Music;

/*
@file AudioManager.h
@brief Audio�̊Ǘ����s��
*/
class AudioManager
{
public:

    /*
    @brief  �C���X�^���X���擾����
    @return AudioManager�N���X�̃C���X�^���X
    */

    static AudioManager* GetInstance() { return audio; }

    /*
    @brief  �C���X�^���X���쐬����
    */
    static void CreateInstance();

    /*
    @brief  �C���X�^���X���폜����
    */
    static void DeleteInstance();
    
    /*
    @fn �ǂݍ��݊֐�(�T�E���h)
    @brief �T�E���h�̓ǂݍ��݂��s��
    @param fileName�@�ǂݍ��ރT�E���h�t�@�C���̃p�X
    */
    Sound* GetSound(const std::string& fileName);
    
    /*
    @fn �폜�֐�(�T�E���h)
    @brief �T�E���h�̍폜���s��
    @param fileName�@�폜����T�E���h�t�@�C���̃p�X
    */
    void RemoveSound(const std::string& fileName);
    
    /*
    @fn �Đ��֐�(�T�E���h)
    @brief �T�E���h�̍Đ����s��
    @param fileName�@�Đ�����T�E���h�t�@�C���̃p�X
    */
    void PlaySound(const std::string& fileName);
    
    /*
    @fn ��~�֐�(�T�E���h)
    @brief �T�E���h�̒�~���s��
    @param fileName�@��~����T�E���h�t�@�C���̃p�X
    */
    void StopSound(const std::string& fileName);
    
    /*
    @fn �Đ���Ԋm�F�֐�(�T�E���h)
    @brief �w�肵���T�E���h���Đ������ǂ����t���O�̎擾
    @param fileName�@�w�肷��T�E���h�t�@�C���̃p�X
    @return bool true �Đ��� : false ��Đ���
    */
    bool IsPlayingSound(const std::string& fileName);
    
    /*
    @fn �ǂݍ��݊֐�(�~���[�W�b�N)
    @brief �~���[�W�b�N�̓ǂݍ��݂��s��
    @param fileName�@�ǂݍ��ރ~���[�W�b�N�t�@�C���̃p�X
    */
    Music* GetMusic(const std::string& fileName);
    
    /*
    @fn �폜�֐�(�~���[�W�b�N)
    @brief �~���[�W�b�N�̍폜���s��
    @param fileName�@�폜����~���[�W�b�N�t�@�C���̃p�X
    */
    void RemoveMusic(const std::string& fileName);
    
    /*
    @fn �t�F�[�h�C���Đ��֐�(�~���[�W�b�N)
    @brief �~���[�W�b�N�̃t�F�[�h�C���Đ����s��
    @param fileName�@�t�F�[�h�C���Đ�����~���[�W�b�N�t�@�C���̃p�X
    */
    void PlayFadeInMusic(const std::string& fileName, int fadeInTime);
    
    /*
    @fn �Đ��֐�(�~���[�W�b�N)
    @brief �~���[�W�b�N���Đ����s��
    @param fileName�@�Đ�����~���[�W�b�N�t�@�C���̃p�X
    */
    void PlayMusic(const std::string& fileName);
    
    /*
    @fn �t�F�[�h�A�E�g�֐�(�~���[�W�b�N)
    @brief �Đ����̃~���[�W�b�N�̃t�F�[�h�A�E�g���s��
    @param fadeOutTime�@�t�F�[�h�A�E�g�ɂ����鎞��
    */
    void FadeOutMusic(int fadeOutTime);

    /*
    @fn ��~�֐�(�~���[�W�b�N)
    @brief �~���[�W�b�N���~���s��
    */
    void StopMusic();
    
    /*
    @fn �Đ���Ԋm�F�֐�(�~���[�W�b�N)
    @brief �~���[�W�b�N���Đ������ǂ����t���O�̎擾
    @return bool true �Đ��� : false ��Đ���
    */
    bool IsPlayingMusic();
    
    /*
    @fn �I�������֐�
    @brief ��������Music�ESound�̉���������s��
    */
    void ShutDown();

private:

    /*
    @fn �R���X�g���N�^
    */
    AudioManager();
    
    /*
    @fn �f�X�g���N�^
    @brife �ێ����Ă���S�Ă�Sound�EMusic���������
    */
    ~AudioManager();

    //�����̃C���X�^���X
    static AudioManager* audio;

    // �t�@�C���l�[����key�Ƃ��Ď���Sound�N���X��Music�N���X�̘A�z�ϒ��z��
    // �ǂݍ��񂾃T�E���h��~���[�W�b�N�̃f�[�^��ێ�����
    std::unordered_map<std::string, class Sound*> mSounds;
    std::unordered_map<std::string, class Music*> mMusics;

};

