//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ThirdStageUI.h"
#include "Renderer.h"
#include "CountDownFont.h"
#include "JumpTutorialParticl.h"
#include "MoveTutorialParticl.h"
#include "StartCountDownSprite.h"
#include "TimeUpSprite.h"
#include "ContinueSprite.h"
#include "GameOverSprite.h"
#include "PlayerObject.h"
#include "SkyBoxObject.h"

/*
@fn �R���X�g���N�^
@brief  object�̐������s��
@param	_playerObject �v���C���[�N���X�̃|�C���^
*/
ThirdStageUI::ThirdStageUI(PlayerObject* _playerObject)
	: GameObject(false, Tag::UI)
	, SceneTime(300)
{
	// �J�E���g�_�E��
	new CountDownFont(SceneTime);
	// start���̃J�E���g�_�E��
	new StartCountDownSprite();
	// �^�C���A�b�v����sprite
	new TimeUpSprite();
	// �R���e�B�j���[�I������sprite
	new ContinueSprite();
	// GameOver����sprite
	new GameOverSprite();
	// �X�J�C�{�b�N�X�𐶐�
	skyBox = new SkyBoxObject(false, Tag::UI);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
ThirdStageUI::~ThirdStageUI()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void ThirdStageUI::UpdateGameObject(float _deltaTime)
{
}