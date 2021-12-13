//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SoundEffectComponent.h"
#include "AudioResourceManager.h"
#include "Sound.h"

/*
@fn �R���X�g���N�^
@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
@param	�T�E���h�̃t�@�C���p�X
@param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
*/
SoundEffectComponent::SoundEffectComponent(GameObject* _owner, const std::string& _fileName, int _updateOrder)
	: AudioComponent(_owner, _fileName ,_updateOrder)
{
	// ���\�[�X�Ǘ��N���X�Ƀt�@�C���l�[����n�����[�h���Ă���������̂����炤
	mySound = AUDIO_RESOURCE->AddSound(_fileName);
}

/*
@fn �f�X�g���N�^
@brief  component�̍폜���s��
*/
SoundEffectComponent::~SoundEffectComponent()
{
	// ���\�[�X�̍폜���Ǘ��҃t�@�C���l�[����n���s��
	AUDIO_RESOURCE->RemoveSound(myFileName);

	if (mySound != nullptr)
	{
		mySound = nullptr;
	}
}

/*
@fn �Đ��֐�(�T�E���h)
@brief �T�E���h�̍Đ����s��
*/
void SoundEffectComponent::Play()
{
	mySound->Play();
}

/*
@fn ��~�֐�(�T�E���h)
@brief �T�E���h�̒�~���s��
*/
void SoundEffectComponent::Stop()
{
	mySound->Stop();
}

/*
@fn �Đ���Ԋm�F�֐�(�T�E���h)
@brief �w�肵���T�E���h���Đ������ǂ����t���O�̎擾
@return bool true �Đ��� : false ��Đ���
*/
bool SoundEffectComponent::IsPlaying()
{

	return 	mySound->IsPlaying();
}

void SoundEffectComponent::SetVolume(int _volume)
{
	mySound->SetChannelVolume(_volume);
}