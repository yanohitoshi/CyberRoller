#include "FinalStageUI.h"
#include "Renderer.h"
#include "CountDownFont.h"
#include "JumpTutorialParticl.h"
#include "MoveTutorialParticl.h"
#include "StartCountDownSprite.h"
#include "TimeUpSprite.h"
#include "ContinueSprite.h"
#include "GameOverSprite.h"
#include "GameClearSprite.h"
#include "PlayerObject.h"

// �ÓI�����o�[������
bool FinalStageUI::timeOverFlag = false;
bool FinalStageUI::countStartFlag = false;

FinalStageUI::FinalStageUI(PlayerObject* _playerObject)
	: GameObject(false, Tag::UI)
	, SceneTime(250)
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

}

FinalStageUI::~FinalStageUI()
{
	// �ÓI�����o�[������
	timeOverFlag = false;
	countStartFlag = false;
}

void FinalStageUI::UpdateGameObject(float _deltaTime)
{
}
