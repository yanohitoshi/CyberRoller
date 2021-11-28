#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SDL.h"
#include <unordered_map>    

// �V���O���g���Ȃ̂ŃC���X�^���X��getter��ÓI�̈��define�Œ�`
#define AUDIO_RESOURCE AudioResourceManager::GetInstance()

// �N���X�̑O���錾
class Sound;
class Music;

/*
@file AudioResourceManager.h
@brief Audio�̊Ǘ����s��
*/
class AudioResourceManager
{
public:

    /*
    @brief  �C���X�^���X���擾����
    @return AudioManager�N���X�̃C���X�^���X
    */

    static AudioResourceManager* GetInstance() { return audioResource; }

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
    Sound* AddSound(const std::string& fileName);
        
    /*
    @fn �폜�֐�(�T�E���h)
    @brief �T�E���h�̍폜���s��
    @param fileName�@�폜����T�E���h�t�@�C���̃p�X
    */
    void RemoveSound(const std::string& fileName);
        
    /*
    @fn �ǂݍ��݊֐�(�~���[�W�b�N)
    @brief �~���[�W�b�N�̓ǂݍ��݂��s��
    @param fileName�@�ǂݍ��ރ~���[�W�b�N�t�@�C���̃p�X
    */
    Music* AddMusic(const std::string& fileName);
    
    /*
    @fn �폜�֐�(�~���[�W�b�N)
    @brief �~���[�W�b�N�̍폜���s��
    @param fileName�@�폜����~���[�W�b�N�t�@�C���̃p�X
    */
    void RemoveMusic(const std::string& fileName);
        
    /*
    @fn �I�������֐�
    @brief ��������Music�ESound�̉���������s��
    */
    void ShutDown();

private:

    /*
    @fn �R���X�g���N�^
    */
    AudioResourceManager();
    
    /*
    @fn �f�X�g���N�^
    @brife �ێ����Ă���S�Ă�Sound�EMusic���������
    */
    ~AudioResourceManager();

    //�����̃C���X�^���X
    static AudioResourceManager* audioResource;

    // �t�@�C���l�[����key�Ƃ��Ď���Sound�N���X��Music�N���X�̘A�z�ϒ��z��
    // �ǂݍ��񂾃T�E���h��~���[�W�b�N�̃f�[�^��ێ�����
    std::unordered_map<std::string, class Sound*> sounds;
    std::unordered_map<std::string, class Music*> musics;

};