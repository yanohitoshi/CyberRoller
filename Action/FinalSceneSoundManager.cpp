//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "FinalSceneSoundManager.h"
#include "AudioResourceManager.h"
#include "MusicComponent.h"
#include "SoundEffectComponent.h"
#include "BaseScene.h"

/*
@fn �R���X�g���N�^
@param �e�N���X�̃V�[���N���X�̃|�C���^
*/
FinalSceneSoundManager::FinalSceneSoundManager(BaseScene* _owner)
	: GameObject(false, Tag::AUDIO)
{
	// �ϐ�������
	owner = _owner;
	isCountDownPlay = true;
	isPlayContinue = true;
	isPlayGameEnd = true;
	isbgmChanged = false;

	// BGM�𐶐�
	bgm = new MusicComponent(this, "Assets/Sound/Bgm/Game/Final.wav");
	gameOverBgm = new MusicComponent(this, "Assets/Sound/Bgm/TimeUp/TimeUp.wav");

	// �T�E���h�G�t�F�N�g�𐶐�
	countDown = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/CountDown/CountDown.wav");
	continueSound = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/Continue/Continue.wav");
	gameEnd = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/GameOver/GameEnd.wav");

}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
FinalSceneSoundManager::~FinalSceneSoundManager()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void FinalSceneSoundManager::UpdateGameObject(float _deltaTime)
{
	// �J�E���g�_�E�������Đ������Ԃ�������
	if (!owner->GetStartScene() && isCountDownPlay)
	{
		// �J�E���g�_�E�������Đ�����
		countDown->Play();
		// �J�E���g�_�E�������Đ����邩��false�ɐ؂�ւ���
		isCountDownPlay = false;
	}

	// �Q�[��BGM���Đ����邩�𔻒�
	bool isPlayBgm = !isCountDownPlay && !owner->GetIsSceneClear() && !owner->GetIsTimeOver();

	// �Đ������Ԃ��Đ�����ċ��Ȃ�������
	if (isPlayBgm && !bgm->IsPlaying())
	{
		// �Q�[��BGM�Đ�����
		bgm->Play();
	}

	// �V�[�����N���A������
	if (owner->GetIsSceneClear())
	{
		// �Q�[��BGM��~����
		bgm->Stop();
	}

	// �^�C���I�[�o�[�ɂȂ���BGM���؂�ւ���Ă��Ȃ�������
	if (owner->GetIsTimeOver() && !isbgmChanged)
	{
		// �Đ�����Ă�����
		if (bgm->IsPlaying())
		{
			// �Q�[��BGM���~
			bgm->Stop();
		}

		// �Q�[���I�[�o�[BGM���Đ�
		gameOverBgm->Play();
		// �؂�ւ��t���O��false�ɂ���
		isbgmChanged = true;
	}

	// �R���e�B�j���[���I������Ă�����
	if (owner->GetIsContinueFlag() && isPlayContinue)
	{
		// �R���e�B�j���[�T�E���h�G�t�F�N�g���Đ�
		continueSound->Play();
		isPlayContinue = false;
	}

	// �Q�[���I�����I������Ă�����
	if (owner->GetIsEndFlag() && isPlayGameEnd)
	{
		gameEnd->Play();
		isPlayGameEnd = false;
	}
}