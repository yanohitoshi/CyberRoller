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
#include "CollectionUI.h"
#include "CollectionObject.h"
/*
@fn �R���X�g���N�^
@brief  object�̐������s��
@param	_playerObject �v���C���[�N���X�̃|�C���^
*/
FinalStageUI::FinalStageUI(PlayerObject* _playerObject, CollectionObject* _first, CollectionObject* _second, CollectionObject* _third)
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
