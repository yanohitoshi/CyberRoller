//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TutorialSceneSoundManager.h"
#include "AudioResourceManager.h"
#include "MusicComponent.h"
#include "BaseScene.h"

/*
@fn �R���X�g���N�^
@param �e�N���X�̃V�[���N���X�̃|�C���^
*/
TutorialSceneSoundManager::TutorialSceneSoundManager(BaseScene* _owner)
	: GameObject(false, Tag::AUDIO)
{
	// �ϐ�������
	owner = _owner;
	isCountDownPlay = true;

	// BGM�𐶐�
	bgm = new MusicComponent(this, "Assets/Sound/Bgm/Tutorial/Tutorial.wav");
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
TutorialSceneSoundManager::~TutorialSceneSoundManager()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void TutorialSceneSoundManager::UpdateGameObject(float _deltaTime)
{
	if (!bgm->IsPlaying())
	{
		bgm->Play();
	}

	if (owner->GetIsSceneClear())
	{
		bgm->Stop();
	}
}