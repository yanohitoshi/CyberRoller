//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ForthStageUI.h"
#include "RenderingObjectManager.h"
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
@param	_first 1�ڂ̎��W���I�u�W�F�N�g�̃|�C���^
@param	_second 2�ڂ̎��W���I�u�W�F�N�g�̃|�C���^
@param	_third 3�ڂ̎��W���I�u�W�F�N�g�̃|�C���^
*/
ForthStageUI::ForthStageUI(PlayerObject* _playerObject, CollectionObject* _first, CollectionObject* _second, CollectionObject* _third)
	: GameObject(false, Tag::UI)
	, SceneTime(300)
	, FirstDrawTime(120)
	, SecondDrawTime(180)
	, ThirdDrawTime(240)
	, FirstCollectionPosition(Vector3(-150.0f, -200.0f, 0.0f))
	, SecondCollectionPosition(Vector3(0.0f, -200.0f, 0.0f))
	, ThirdCollectionPosition(Vector3(150.0f, -200.0f, 0.0f))
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
ForthStageUI::~ForthStageUI()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void ForthStageUI::UpdateGameObject(float _deltaTime)
{
	// �V�[�����N���A������
	if (playerObject->GetClearFlag())
	{
		// �J�E���g�𐔂���
		++clearCount;

		// �|�W�V���������ʂ��o���ꏊ�Ɉړ����Ă��Ȃ�������
		if (!isChangePosition)
		{
			// ���ꂼ��|�W�V�������Z�b�g���ĕ`���Ԃ����Z�b�g
			firstCollectionUI->SetDrawPosition(FirstCollectionPosition);
			firstCollectionUI->ResetDraw();

			secondCollectionUI->SetDrawPosition(SecondCollectionPosition);
			secondCollectionUI->ResetDraw();

			thirdCollectionUI->SetDrawPosition(ThirdCollectionPosition);
			thirdCollectionUI->ResetDraw();
			isChangePosition = true;
		}

		// ���ꂼ�ꎞ�Ԃ�������`�悷��
		if (clearCount >= FirstDrawTime)
		{
			firstCollectionUI->DrawInGame();
		}

		if (clearCount >= SecondDrawTime)
		{
			secondCollectionUI->DrawInGame();
		}

		if (clearCount >= ThirdDrawTime)
		{
			thirdCollectionUI->DrawInGame();
		}
	}
	else
	{
		// �`�悷��
		firstCollectionUI->DrawInGame();
		secondCollectionUI->DrawInGame();
		thirdCollectionUI->DrawInGame();
	}
}
