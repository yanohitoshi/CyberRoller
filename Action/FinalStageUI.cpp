//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "FinalStageUI.h"
#include "Renderer.h"
#include "CountDownFont.h"
#include "StartCountDownSprite.h"
#include "TimeUpSprite.h"
#include "ContinueSprite.h"
#include "GameOverSprite.h"
#include "GameClearSprite.h"
#include "PlayerObject.h"
#include "SkyBoxObject.h"

/*
@fn �R���X�g���N�^
@brief  object�̐������s��
@param	_playerObject �v���C���[�N���X�̃|�C���^
*/
FinalStageUI::FinalStageUI(PlayerObject* _playerObject)
	: GameObject(false, Tag::UI)
	, SceneTime(500)
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
	// GameClear����sprite
	new GameClearSprite(_playerObject);

	skyBox = new SkyBoxObject(false, Tag::UI);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
FinalStageUI::~FinalStageUI()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void FinalStageUI::UpdateGameObject(float _deltaTime)
{
}
