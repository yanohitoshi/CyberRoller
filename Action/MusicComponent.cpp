//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "MusicComponent.h"
#include "AudioResourceManager.h"
#include "Music.h"

/*
@brief	�R���X�g���N�^
@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
@param	�ǂݍ��ރT�E���h�t�@�C���̃p�X
@param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
*/
MusicComponent::MusicComponent(GameObject* _owner, const std::string& _fileName, int _updateOrder)
	: AudioComponent(_owner, _fileName, _updateOrder)
{
	// ���\�[�X�Ǘ��N���X�Ƀt�@�C���l�[����n�����[�h���Ă���������̂����炤
	myMusic = AUDIO_RESOURCE->AddMusic(_fileName);
}

/*
@fn �f�X�g���N�^
@brief  component�̍폜���s��
*/
MusicComponent::~MusicComponent()
{
	// ���\�[�X�̍폜���Ǘ��҃t�@�C���l�[����n���s��
	AUDIO_RESOURCE->RemoveMusic(myFileName);
}

/*
@fn �t�F�[�h�C���Đ��֐�(�~���[�W�b�N)
@brief �~���[�W�b�N�̃t�F�[�h�C���Đ����s��
@param fadeInTime�@�t�F�[�h�C���ɂ����鎞��
*/
void MusicComponent::PlayFadeIn(int _fadeInTime)
{
	myMusic->FadeInMusic(_fadeInTime);
}

/*
@fn �Đ��֐�(�~���[�W�b�N)
@brief �~���[�W�b�N���Đ����s��
*/
void MusicComponent::Play()
{
	myMusic->Play();
}

/*
@fn �t�F�[�h�A�E�g�֐�(�~���[�W�b�N)
@brief �Đ����̃~���[�W�b�N�̃t�F�[�h�A�E�g���s��
@param fadeOutTime�@�t�F�[�h�A�E�g�ɂ����鎞��
*/
void MusicComponent::FadeOut(int _fadeOutTime)
{
	myMusic->FadeOutMusic(_fadeOutTime);
}

/*
@fn ��~�֐�(�~���[�W�b�N)
@brief �~���[�W�b�N���~���s��
*/
void MusicComponent::Stop()
{
	myMusic->Stop();
}

/*
@fn �Đ���Ԋm�F�֐�(�~���[�W�b�N)
@brief �~���[�W�b�N���Đ������ǂ����t���O�̎擾
@return bool true �Đ��� : false ��Đ���
*/
bool MusicComponent::IsPlaying()
{
	return myMusic->IsPlaying();
}