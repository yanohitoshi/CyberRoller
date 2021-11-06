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
#include "CollectionUI.h"
#include "CollectionObject.h"

/*
@fn �R���X�g���N�^
@brief  object�̐������s��
@param	_playerObject �v���C���[�N���X�̃|�C���^
*/
ThirdStageUI::ThirdStageUI(PlayerObject* _playerObject, CollectionObject* _first, CollectionObject* _second, CollectionObject* _third)
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

	playerObject = _playerObject;

	firstCollectionUI = new CollectionUI(_first);
	secondCollectionUI = new CollectionUI(_second);
	thirdCollectionUI = new CollectionUI(_third);

	clearCount = 0;
	isChangePosition = false;
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
	if (playerObject->GetClearFlag())
	{
		++clearCount;

		if (!isChangePosition)
		{
			firstCollectionUI->SetDrawPosition(Vector3(-150.0f, 0.0f, 0.0f));
			firstCollectionUI->ResetDraw();

			secondCollectionUI->SetDrawPosition(Vector3(0.0f, 0.0f, 0.0f));
			secondCollectionUI->ResetDraw();

			thirdCollectionUI->SetDrawPosition(Vector3(150.0f, 0.0f, 0.0f));
			thirdCollectionUI->ResetDraw();
			isChangePosition = true;
		}

		if (clearCount >= 120)
		{
			firstCollectionUI->DrawInGame();
		}

		if (clearCount >= 180)
		{
			secondCollectionUI->DrawInGame();
		}

		if (clearCount >= 240)
		{
			thirdCollectionUI->DrawInGame();
		}
	}
	else
	{
		firstCollectionUI->DrawInGame();
		secondCollectionUI->DrawInGame();
		thirdCollectionUI->DrawInGame();
	}
}