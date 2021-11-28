//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "AudioResourceManager.h"
#include "Music.h"
#include "Sound.h"

AudioResourceManager* AudioResourceManager::audioResource = nullptr;

/*
@fn �R���X�g���N�^
*/
AudioResourceManager::AudioResourceManager()
{
}

/*
@fn �f�X�g���N�^
@brife �ێ����Ă���S�Ă�Sound�EMusic���������
*/
AudioResourceManager::~AudioResourceManager()
{
    if (sounds.size() > 0 || musics.size() > 0)
    {
        ShutDown();
    }
}

/*
@brief  �C���X�^���X���쐬����
*/
void AudioResourceManager::CreateInstance()
{
    if (audioResource == nullptr)
    {
        audioResource = new AudioResourceManager();
    }
}

/*
@brief  �C���X�^���X���폜����
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
@fn �ǂݍ��݊֐�(�T�E���h)
@brief �T�E���h�̓ǂݍ��݂��s��
@param fileName�@�ǂݍ��ރT�E���h�t�@�C���̃p�X
*/
Sound* AudioResourceManager::AddSound(const std::string& fileName)
{
    Sound* sound = nullptr;//�T�E���h�N���X�̃|�C���^(������)
    auto iter = sounds.find(fileName);//�t�@�C�����̌���
    // �T�E���h�t�@�C���o�^����Ă��邩�H
    if (iter != sounds.end())//�T�E���h���������������̂�
    {
        sound = iter->second;//�T�E���h����������
    }
    else
    {
        // �o�^�Ȃ�������V�K�T�E���h�ǂݍ���
        sound = new Sound();
        if (sound->LoadSound(fileName))
        {
            sounds.emplace(fileName, sound);//����mSounds[fileName] = sound;�����Ă���
        }
        else
        {
            printf("%s �ǂݍ��ݎ��s\n", fileName.c_str());
            delete sound;
            sound = nullptr;
        }
    }

    return sound;
}

/*
@fn �폜�֐�(�T�E���h)
@brief �T�E���h�̍폜���s��
@param fileName�@�폜����T�E���h�t�@�C���̃p�X
*/
void AudioResourceManager::RemoveSound(const std::string& fileName)
{
    // �T�E���h�t�@�C�����폜
    auto iter = sounds.find(fileName);
    if (iter != sounds.end())
    {
        printf("release: %s\n", iter->first.c_str());
        delete iter->second;
        sounds.erase(iter);
    }
}

/*
@fn �ǂݍ��݊֐�(�~���[�W�b�N)
@brief �~���[�W�b�N�̓ǂݍ��݂��s��
@param fileName�@�ǂݍ��ރ~���[�W�b�N�t�@�C���̃p�X
*/
Music* AudioResourceManager::AddMusic(const std::string& fileName)
{
    Music* music = nullptr;//������
    auto iter = musics.find(fileName);//�t�@�C�����̌���
    //�~���[�W�b�N�t�@�C���o�^����Ă��邩�H
    if (iter != musics.end())//�~���[�W�b�N���������������̂�
    {
        music = iter->second;//�~���[�W�b�N����������
    }
    else
    {
        //�o�^���Ȃ�������V�K�~���[�W�b�N�ǂݍ���
        music = new Music();
        if (music->LoadMusic(fileName))
        {
            musics.emplace(fileName, music);
        }
        else
        {
            printf("%s�ǂݍ��ݎ��s\n", fileName.c_str());
            delete music;
            music = nullptr;
        }
    }
    return music;
}

/*
@fn �폜�֐�(�~���[�W�b�N)
@brief �~���[�W�b�N�̍폜���s��
@param fileName�@�폜����~���[�W�b�N�t�@�C���̃p�X
*/
void AudioResourceManager::RemoveMusic(const std::string& fileName)
{
    //�~���[�W�b�N�t�@�C�����폜
    auto iter = musics.find(fileName);
    if (iter != musics.end())
    {
        printf("release: %s\n", iter->first.c_str());
        delete iter->second;
        musics.erase(iter);
    }
}

/*
@fn �I�������֐�
@brief ��������Music�ESound�̉���������s��
*/
void AudioResourceManager::ShutDown()
{
    //�T�E���h�j��
    for (auto i : sounds)
    {
        printf("release : %s\n", i.first.c_str());
        delete i.second;
    }
    sounds.clear();
    //�~���[�W�b�N�j���R�[�h�������ɏ���
    for (auto i : musics)
    {
        printf("release : %s\n", i.first.c_str());
        delete i.second;
    }
    musics.clear();
}