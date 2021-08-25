
/*�������Ȃ̂Ŏg�p���Ă��܂���*/

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
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
@brief  �C���X�^���X���쐬����
*/
void AudioManager::CreateInstance()
{
    if (audio == nullptr)
    {
        audio = new AudioManager();
    }
}

/*
@brief  �C���X�^���X���폜����
*/
void AudioManager::DeleteInstance()
{
    if (audio != nullptr)
    {
        delete audio;
        audio = nullptr;
    }
}

// �T�E���h�擾
Sound* AudioManager::GetSound(const std::string& fileName)
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

void AudioManager::RemoveSound(const std::string& fileName)
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

void AudioManager::PlaySound(const std::string& fileName)
{
    //�T�E���h�炷
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
    return nullptr;
}

void AudioManager::RemoveMusic(const std::string& fileName)
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

void AudioManager::PlayFadeInMusic(const std::string& fileName, int fadeInTime)
{
    musics[fileName]->FadeInMusic(fadeInTime);
}

void AudioManager::PlayMusic(const std::string& fileName)
{
    //�~���[�W�b�N��炷
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